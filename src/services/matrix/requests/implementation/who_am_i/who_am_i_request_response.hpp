#pragma once

#include "../../../../serialization/deserializable.hpp"
#include <string>

namespace epsilon::services::matrix::requests::implementation::who_am_i {

struct WhoAmIRequestResponse {
    std::string UserId;
};

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::who_am_i::WhoAmIRequestResponse Deserialize<requests::implementation::who_am_i::WhoAmIRequestResponse>(SerializationPrimitive primitive);

}