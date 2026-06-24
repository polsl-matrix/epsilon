#pragma once

#include "../services/matrix/requests/authenticated_request_manager.hpp"

#include "user.hpp"

#include <memory>
#include <string>

namespace epsilon::model {

class Session {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;

    std::shared_ptr<RequestManager> m_RequestManager;

public:
    Session(std::shared_ptr<RequestManager> request_manager);

    User CurrentUser() const;
};

}