#include "registration_request_response.hpp"
#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"
#include <string>

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::registration::RegistrationRequestResponse
Deserialize<requests::implementation::registration::RegistrationRequestResponse>(
    SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto access_token = ReadField<String>(reply, "access_token");
    const auto refresh_token = ReadField<String>(reply, "refresh_token");
    const auto user_id = ReadField<String>(reply, "user_id");

    return requests::implementation::registration::RegistrationRequestResponse{
        access_token.value,
        refresh_token.value,
        user_id.value
    };
}

}