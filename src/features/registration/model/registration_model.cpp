#include "registration_model.hpp"
#include "../../../core/future/future.hpp"
#include "../../../services/matrix/requests/implementation/common/error.hpp"
#include "../../../services/matrix/requests/implementation/registration/registration_request.hpp"
#include "../../../services/matrix/requests/implementation/registration/registration_request_body.hpp"
#include "../../../services/matrix/requests/implementation/registration/registration_request_response.hpp"
#include "registration_error.hpp"

#include <expected>
#include <optional>
#include <string>
#include <utility>

using epsilon::core::future::Future;
using epsilon::services::matrix::requests::implementation::common::Error;
using epsilon::services::matrix::requests::implementation::registration::
    RegistrationRequest;
using epsilon::services::matrix::requests::implementation::registration::
    RegistrationRequestBody;
using epsilon::services::matrix::requests::implementation::registration::
    RegistrationRequestResponse;

namespace epsilon::features::registration {

RegistrationModel::RegistrationModel(
    std::shared_ptr<RequestManager> request_manager)
    : m_RequestManager(std::move(request_manager)) {}

std::shared_ptr<Future<RegistrationModel::Result>::Handle>
RegistrationModel::Register(const std::string &username,
                            const std::string &password) {
    auto reg_future = std::make_shared<Future<Result>>();

    auto request = RegistrationRequest();
    request.SetBody(RegistrationRequestBody{ username, password });

    m_RequestManager
        ->Execute<RegistrationRequestBody, RegistrationRequestResponse, Error>(
            request, [reg_future](auto reply) {
                if (!reply.has_value()) {
                    reg_future->Realize(
                        std::unexpected(RegistrationError::RequestFailed));
                    return;
                }

                if (reply->StatusCode != 200 || !reply->Body.has_value()) {
                    const auto error = reply->Body.error();

                    if (error.ErrorCode() == "M_USER_IN_USE") {
                        reg_future->Realize(
                            std::unexpected(RegistrationError::UsernameTaken));
                    } else if (reply->StatusCode == 429) {
                        reg_future->Realize(std::unexpected(
                            RegistrationError::ReachedRequestLimit));
                    } else {
                        reg_future->Realize(
                            std::unexpected(RegistrationError::UnknownError));
                    }

                    return;
                }

                const auto reg_data = reply->Body.value();

                reg_future->Realize(RegistrationResult{ reg_data.AccessToken,
                                                        reg_data.RefreshToken,
                                                        reg_data.UserId });
            });

    return reg_future->GetHandle();
}

std::shared_ptr<RegistrationModel::RequestManager>
RegistrationModel::GetRequestManager() {
    return m_RequestManager;
}

} // namespace epsilon::features::registration