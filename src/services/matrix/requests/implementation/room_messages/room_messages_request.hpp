#pragma once

#include "room_messages_request_response.hpp"
#include "../common/empty.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

#include <string>

namespace epsilon::services::matrix::requests::implementation::room_messages {

class RoomMessagesRequest : public Request<common::Empty, RoomMessagesRequestResponse, common::Error> {
    std::string m_RoomId;

public:
    explicit RoomMessagesRequest(std::string room_id);

    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

} // namespace epsilon::services::matrix::requests::implementation::room_messages