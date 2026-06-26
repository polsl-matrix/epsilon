#pragma once

#include "../../../../serialization/deserializable.hpp"

#include <optional>
#include <string>

namespace epsilon::services::matrix::requests::implementation::profile {

struct ProfileRequestResponse {
    std::optional<std::string> DisplayName;
    std::optional<std::string> AvatarUrl;
};

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::profile::ProfileRequestResponse Deserialize<requests::implementation::profile::ProfileRequestResponse>(SerializationPrimitive primitive);

}