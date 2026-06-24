#pragma once

#include "../../../../serialization/deserializable.hpp"

#include <string>
#include <vector>

namespace epsilon::services::matrix::requests::implementation::room_messages {

struct ExtractedMessage {
    std::string Sender;
    std::string Body;
};

struct RoomMessagesRequestResponse {
    std::string StartToken;
    std::string EndToken;
    std::vector<ExtractedMessage> Messages;
};

} // namespace epsilon::services::matrix::requests::implementation::room_messages

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::room_messages::RoomMessagesRequestResponse 
Deserialize<requests::implementation::room_messages::RoomMessagesRequestResponse>(SerializationPrimitive primitive);

} // namespace epsilon::services::matrix::serialization