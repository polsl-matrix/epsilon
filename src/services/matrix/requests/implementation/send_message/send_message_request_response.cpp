#include "send_message_request_response.hpp"

#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"
#include "../../../../serialization/serialization_primitive.hpp"

#include <string>

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::send_message::SendMessageRequestResponse
Deserialize<requests::implementation::send_message::SendMessageRequestResponse>(
    SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto event_id = ReadField<String>(reply, "event_id").value;

    return requests::implementation::send_message::SendMessageRequestResponse{
        event_id
    };
}

} // namespace epsilon::services::matrix::serialization