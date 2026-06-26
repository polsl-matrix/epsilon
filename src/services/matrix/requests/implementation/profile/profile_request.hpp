#pragma once

#include "profile_request_response.hpp"
#include "../common/empty.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

#include <string>

namespace epsilon::services::matrix::requests::implementation::profile {

class ProfileRequest : public Request<common::Empty, ProfileRequestResponse, common::Error> {
    std::string m_UserId;

public:
    ProfileRequest(std::string user_id);

    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

}