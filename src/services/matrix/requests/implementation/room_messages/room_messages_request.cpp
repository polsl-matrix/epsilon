#include "room_messages_request.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

#include <utility>

namespace epsilon::services::matrix::requests::implementation::room_messages {

RoomMessagesRequest::RoomMessagesRequest(std::string room_id)
    : m_RoomId(std::move(room_id)) {}

HttpMethod RoomMessagesRequest::Method() const { return HttpMethod::GET; }

std::string RoomMessagesRequest::Endpoint() const {
    return "/_matrix/client/v3/rooms/" + m_RoomId + "/messages";
}

} // namespace
  // epsilon::services::matrix::requests::implementation::room_messages