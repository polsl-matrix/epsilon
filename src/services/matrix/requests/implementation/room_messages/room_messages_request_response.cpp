#include "room_messages_request_response.hpp"

#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"

#include <chrono>
#include <sstream>
#include <string>
#include <vector>

using epsilon::services::matrix::serialization::Expect;
using epsilon::services::matrix::serialization::RArray;
using epsilon::services::matrix::serialization::ReadField;
using epsilon::services::matrix::serialization::ReadFieldOptional;
using epsilon::services::matrix::serialization::RObject;
using epsilon::services::matrix::serialization::String;

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::room_messages::RoomMessagesRequestResponse
Deserialize<
    requests::implementation::room_messages::RoomMessagesRequestResponse>(
    SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto chunk_primitive = ReadField<RArray>(reply, "chunk");
    const auto &chunk_array = chunk_primitive.get().values;

    std::vector<requests::implementation::room_messages::ExtractedMessage>
        messages;

    for (const auto &element : chunk_array) {
        const auto event_obj = Expect<RObject>(element).get();

        // We only parse messages, not the other types of events
        const auto type_field = ReadFieldOptional<String>(event_obj, "type");
        if (!type_field.has_value() || type_field->value != "m.room.message") {
            continue;
        }

        const auto sender_field = ReadField<String>(event_obj, "sender");
        const auto timestamp_string = ReadField<String>(event_obj, "origin_server_ts");

        const std::istringstream string_stream{timestamp_string.value};
        std::chrono::sys_time<std::chrono::microseconds> timestamp;

        // TODO: Add exception handling
        string_stream >> std::chrono::parse("%FT%T%Ez", timestamp);

        const auto content_obj = ReadField<RObject>(event_obj, "content").get();
        const auto body_field =
            ReadFieldOptional<String>(content_obj, "membership");

        if (body_field.has_value()) {
            messages.push_back({ sender_field.value, body_field->value });
        }
    }

    return requests::implementation::room_messages::RoomMessagesRequestResponse{
        std::move(messages)
    };
}

} // namespace epsilon::services::matrix::serialization