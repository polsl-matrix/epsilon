#pragma once

#include "../../../services/matrix/requests/request_manager.hpp"

#include <memory>
#include <string>

namespace epsilon::features::login {

class LoginModel {
    using RequestManager = services::matrix::requests::RequestManager;
  
    std::unique_ptr<RequestManager> m_RequestManager;

  public:
    LoginModel(std::unique_ptr<RequestManager>&& request_manager);

    // TODO: It's not an email, it's a username
    bool Authenticate(const std::string &email, const std::string &password);
};

}
