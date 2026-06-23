#include "login_request_response.hpp"

#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"

#include <optional>
#include <string>

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::login::LoginRequestResponse
Deserialize<requests::implementation::login::LoginRequestResponse>(
    SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto access_token = ReadField<String>(reply, "access_token");
    const auto device_id = ReadFieldOptional<String>(reply, "device_id");
    const auto user_id = ReadField<String>(reply, "user_id");

    return requests::implementation::login::LoginRequestResponse{
        access_token.value, device_id.transform([](const auto device_id) {
            return device_id.value;
        }),
        user_id.value
    };
}

} // namespace epsilon::services::matrix::serialization