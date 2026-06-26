#pragma once

#include "send_message_request_body.hpp"
#include "send_message_request_response.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

#include <string>

namespace epsilon::services::matrix::requests::implementation::send_message {

class SendMessageRequest : public Request<SendMessageRequestBody, SendMessageRequestResponse, common::Error> {
    static uint32_t m_TxnId;
    std::string m_RoomId;

public:
    SendMessageRequest(std::string room_id);

    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

}
