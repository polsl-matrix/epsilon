#pragma once

#include "joined_rooms_request_response.hpp"
#include "../common/empty.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::joined_rooms {

class JoinedRoomsRequest : public Request<common::Empty, JoinedRoomsRequestResponse, common::Error> {
public:
    using Request<common::Empty, JoinedRoomsRequestResponse, common::Error>::Request;

    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

} // namespace epsilon::services::matrix::requests::implementation::joined_rooms