#include "login_model.hpp"

#include "login_error.hpp"
#include "../../../services/matrix/requests/implementation/common/error.hpp"
#include "../../../services/matrix/requests/implementation/login/login_request_body.hpp"
#include "../../../services/matrix/requests/implementation/login/login_request_response.hpp"
#include "../../../services/matrix/requests/implementation/login/login_request.hpp"
#include "../../../core/future/future.hpp"

#include <expected>
#include <optional>
#include <string>
#include <utility>
#include <iostream>

using epsilon::core::future::Future;
using epsilon::services::matrix::requests::implementation::common::Error;
using epsilon::services::matrix::requests::implementation::login::LoginRequestBody;
using epsilon::services::matrix::requests::implementation::login::LoginRequestResponse;
using epsilon::services::matrix::requests::implementation::login::LoginRequest;

namespace epsilon::features::login {

LoginModel::LoginModel(std::unique_ptr<RequestManager>&& request_manager) : m_RequestManager(std::move(request_manager)) {}

std::shared_ptr<Future<LoginModel::Result>::Handle> LoginModel::Authenticate(const std::string &email,
                              const std::string &password)
{
    auto login_future = std::make_shared<Future<Result>>();

    auto request = LoginRequest();

    request.SetBody(LoginRequestBody { email, password });

    m_RequestManager->Execute<LoginRequestBody, LoginRequestResponse, Error>(
        request,
        [login_future](auto reply) {
            if(!reply.has_value()) {
                login_future->Realize(std::unexpected(LoginError::RequestFailed));
                return;
            }

            std::cout << "Received reply. Status code: " << reply->StatusCode << '\n';

            if(reply->StatusCode != 200 || !reply->Body.has_value()) {
                const auto error = reply->Body.error();

                if(error.ErrorCode() == "M_FORBIDDEN") {
                    login_future->Realize(std::unexpected(LoginError::IncorrectAuthenticationData));
                } else if(error.ErrorCode() == "M_USER_DEACTIVATED") {
                    login_future->Realize(std::unexpected(LoginError::UserDeactivated));
                } else if(reply->StatusCode == 429) {
                    login_future->Realize(std::unexpected(LoginError::ReachedRequestLimit));
                } else {
                    login_future->Realize(std::unexpected(LoginError::UnknownError));
                }

                return;
            }

            const auto login_data = reply->Body.value();

            login_future->Realize(LoginResult { login_data.AccessToken });
        }
    );

    return login_future->GetHandle();
}

}