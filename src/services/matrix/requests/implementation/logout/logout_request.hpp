#pragma once

#include "../common/empty.hpp"
#include "../common/error.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::logout {

class LogoutRequest : public Request<common::Empty, common::Empty, common::Error> {
public:
    using Request<common::Empty, common::Empty, common::Error>::Request;

    virtual HttpMethod Method() const override;
    virtual std::string Endpoint() const override;
};

}
