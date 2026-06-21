#pragma once

#include "login_error.hpp"
#include "login_result.hpp"
#include "../../../services/matrix/requests/request_manager.hpp"
#include "../../../core/future/future.hpp"

#include <expected>
#include <memory>
#include <string>

namespace epsilon::features::login {

class LoginModel {
    using RequestManager = services::matrix::requests::RequestManager;
    template<typename T>
    using Future = epsilon::core::future::Future<T>;
    using Result = std::expected<LoginResult, LoginError>;
  
    std::unique_ptr<RequestManager> m_RequestManager;

  public:
    LoginModel(std::unique_ptr<RequestManager>&& request_manager);

    /// @brief Authenticates the user with the given credentials
    /// @returns The received access token or an authentication error
    std::shared_ptr<Future<Result>::Handle> Authenticate(const std::string &username, const std::string &password);
};

}
