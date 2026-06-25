#include "who_am_i_request_response.hpp"
#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"
#include <string>

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::who_am_i::WhoAmIRequestResponse
Deserialize<requests::implementation::who_am_i::WhoAmIRequestResponse>(
    SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto user_id = ReadField<String>(reply, "userId");

    return requests::implementation::who_am_i::WhoAmIRequestResponse{
        user_id.value
    };
}

} // namespace epsilon::services::matrix::serialization