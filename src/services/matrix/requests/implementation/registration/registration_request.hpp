#pragma once

#include "registration_request_body.hpp"
#include "registration_request_response.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::registration {

class RegistrationRequest : public Request<RegistrationRequestBody, RegistrationRequestResponse, common::Error> {
public:
    using Request<RegistrationRequestBody, RegistrationRequestResponse, common::Error>::Request;

    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

}