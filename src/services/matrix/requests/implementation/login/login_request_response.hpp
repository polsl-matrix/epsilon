#pragma once

#include "../../../../serialization/deserializable.hpp"

#include <optional>
#include <string>

namespace epsilon::services::matrix::requests::implementation::login {

struct LoginRequestResponse {
    std::string AccessToken;
    std::optional<std::string> DeviceId;
    std::string UserId;
};

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::login::LoginRequestResponse Deserialize<requests::implementation::login::LoginRequestResponse>(SerializationPrimitive primitive);

}