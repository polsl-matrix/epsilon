#include "login_model.hpp"

#include <string>
#include <utility>

namespace epsilon::features::login {

LoginModel::LoginModel(std::unique_ptr<RequestManager>&& request_manager) : m_RequestManager(std::move(request_manager)) {}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool LoginModel::Authenticate(const std::string &email,
                              const std::string &password) {
    return email == "test" && password == "test";
}

}