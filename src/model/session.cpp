#include "session.hpp"

#include "../services/matrix/requests/authenticated_request_manager.hpp"
#include "../services/matrix/requests/implementation/who_am_i/who_am_i_request.hpp"
#include "../core/future/future.hpp"

#include "user.hpp"

#include <expected>
#include <memory>
#include <string>
#include <utility>

namespace epsilon::model {

Session::Session(std::shared_ptr<RequestManager> request_manager)
    : m_RequestManager(std::move(request_manager)) {}

std::shared_ptr<core::future::Future<Session::Result>::Handle> Session::CurrentUser() const {
    using namespace epsilon::services::matrix::requests::implementation::who_am_i;
    using namespace epsilon::services::matrix::requests::implementation::common;
    using namespace core::future;

    auto user_future = std::make_shared<Future<Result>>();

    auto request = WhoAmIRequest();

    m_RequestManager->Execute<Empty, WhoAmIRequestResponse, Error>(
        request,
        [request_manager = m_RequestManager, user_future](auto reply) {
            if(!reply.has_value()) {
                user_future->Realize(
                    std::unexpected(SessionUserError::RequestFailed));
                return;
            }

            if (reply->StatusCode == 401) {
                user_future->Realize(
                    std::unexpected(SessionUserError::AuthorizationError));
                return;
            }

            if (reply->StatusCode != 200 || !reply->Body.has_value()) {
                user_future->Realize(
                    std::unexpected(SessionUserError::UnknownError));
                return;
            }

            const auto &response_data = reply->Body.value();

            user_future->Realize(User(request_manager, response_data.UserId));
        }
    );

    return user_future->GetHandle();
}

} // namespace epsilon::model