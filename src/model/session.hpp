#pragma once

#include "../services/matrix/requests/authenticated_request_manager.hpp"
#include "../core/future/future.hpp"

#include "user.hpp"

#include <expected>
#include <memory>
#include <string>

namespace epsilon::model {

enum class SessionUserError {
    RequestFailed,
    AuthorizationError,
    UnknownError
};

class Session {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;

    std::shared_ptr<RequestManager> m_RequestManager;

public:
    Session(std::shared_ptr<RequestManager> request_manager);

    using Result = std::expected<User, SessionUserError>;

    std::shared_ptr<core::future::Future<Result>::Handle> CurrentUser() const;
};

}