#include "profile_request_response.hpp"

#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"

#include <string>

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::profile::ProfileRequestResponse
Deserialize<requests::implementation::profile::ProfileRequestResponse>(
    SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto display_name = ReadFieldOptional<String>(reply, "displayname");
    const auto avatar_url = ReadFieldOptional<String>(reply, "avatar_url");

    return requests::implementation::profile::ProfileRequestResponse{
        display_name.transform(
            [](const auto &display_name) { return display_name.value; }),
        avatar_url.transform(
            [](const auto &avatar_url) { return avatar_url.value; })
    };
}

} // namespace epsilon::services::matrix::serialization