#pragma once

#include "login_request_body.hpp"
#include "login_request_response.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::login {

class LoginRequest : public Request<LoginRequestBody, LoginRequestResponse, common::Error> {
public:
    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

}
