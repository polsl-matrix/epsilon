#include "send_message_request.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

#include <cstdlib>
#include <string>
#include <time.h>
#include <utility>

namespace epsilon::services::matrix::requests::implementation::send_message {

uint32_t SendMessageRequest::m_TxnId = std::rand();

SendMessageRequest::SendMessageRequest(std::string room_id) : m_RoomId(std::move(room_id)) {
    std::srand(time(0));

    m_TxnId = std::rand();
}

HttpMethod SendMessageRequest::Method() const { return HttpMethod::PUT; }

std::string SendMessageRequest::Endpoint() const {
    return "/_matrix/client/v3/rooms/" + m_RoomId + "/send/m.room.message/" +
           std::to_string(m_TxnId++);
}

}; // namespace
   // epsilon::services::matrix::requests::implementation::send_message
