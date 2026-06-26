#pragma once

#include "../../../../serialization/deserializable.hpp"

#include <string>

namespace epsilon::services::matrix::requests::implementation::send_message {

struct SendMessageRequestResponse {
    std::string EventId;
};

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::send_message::SendMessageRequestResponse Deserialize<requests::implementation::send_message::SendMessageRequestResponse>(SerializationPrimitive primitive);

}