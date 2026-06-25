#pragma once

#include "who_am_i_request_response.hpp"
#include "../common/empty.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::who_am_i {

class WhoAmIRequest : public Request<common::Empty, WhoAmIRequestResponse, common::Error> {
public:
    using Request<common::Empty, WhoAmIRequestResponse, common::Error>::Request;

    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

}