#pragma once

#include "../../../../serialization/deserializable.hpp"
#include <string>

namespace epsilon::services::matrix::requests::implementation::registration {

struct RegistrationRequestResponse {
    std::string AccessToken;
    std::string RefreshToken;
    std::string UserId;
};

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::registration::RegistrationRequestResponse Deserialize<requests::implementation::registration::RegistrationRequestResponse>(SerializationPrimitive primitive);

}