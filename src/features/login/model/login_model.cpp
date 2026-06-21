#include "login_model.hpp"

#include "../../../services/matrix/requests/implementation/common/error.hpp"
#include "../../../services/matrix/requests/implementation/login/login_request_body.hpp"
#include "../../../services/matrix/requests/implementation/login/login_request_response.hpp"
#include "../../../services/matrix/requests/implementation/login/login_request.hpp"

#include <optional>
#include <string>
#include <utility>

using epsilon::services::matrix::requests::implementation::common::Error;
using epsilon::services::matrix::requests::implementation::login::LoginRequestBody;
using epsilon::services::matrix::requests::implementation::login::LoginRequestResponse;
using epsilon::services::matrix::requests::implementation::login::LoginRequest;

namespace epsilon::features::login {

LoginModel::LoginModel(std::unique_ptr<RequestManager>&& request_manager) : m_RequestManager(std::move(request_manager)) {}

bool LoginModel::Authenticate(const std::string &email,
                              const std::string &password)
{
    auto request = LoginRequest();

    request.SetBody(LoginRequestBody { email, password });

    m_RequestManager->Execute<LoginRequestBody, LoginRequestResponse, Error>(
        request,
        [](std::optional<RequestManager::Reply<LoginRequestResponse, Error>>) {

    });

    return email == "test" && password == "test";
}

}