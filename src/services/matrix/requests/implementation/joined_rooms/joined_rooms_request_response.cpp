#include "joined_rooms_request_response.hpp"

#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"

#include <string>
#include <vector>

using epsilon::services::matrix::serialization::Expect;
using epsilon::services::matrix::serialization::RArray;
using epsilon::services::matrix::serialization::ReadField;
using epsilon::services::matrix::serialization::RObject;
using epsilon::services::matrix::serialization::String;

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::joined_rooms::JoinedRoomsRequestResponse
Deserialize<requests::implementation::joined_rooms::JoinedRoomsRequestResponse>(
    SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto rooms_primitive = ReadField<RArray>(reply, "joined_rooms");
    const auto &rooms_array = rooms_primitive.get().values;

    std::vector<std::string> joined_rooms;
    joined_rooms.reserve(rooms_array.size());

    for (const auto &element : rooms_array) {
        const auto room_str = Expect<String>(element);
        joined_rooms.push_back(room_str.value);
    }

    return requests::implementation::joined_rooms::JoinedRoomsRequestResponse{
        std::move(joined_rooms)
    };
}

} // namespace epsilon::services::matrix::serialization