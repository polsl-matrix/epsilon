#include "user.hpp"

#include "../services/matrix/requests/authenticated_request_manager.hpp"
#include "../services/matrix/requests/implementation/profile/profile_request.hpp"
#include "../services/matrix/requests/implementation/profile/profile_request_response.hpp"
#include "../services/matrix/requests/implementation/common/empty.hpp"
#include "../services/matrix/requests/implementation/common/error.hpp"
#include "../core/future/future.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>

using epsilon::core::future::Future;

namespace epsilon::model {

User::User(std::shared_ptr<RequestManager> request_manager, std::string id)
    : m_RequestManager(std::move(request_manager)), m_Id(std::move(id)) {}

std::string User::Id() const { return m_Id; }

std::shared_ptr<core::future::Future<std::string>::Handle> User::Name() const {
    auto user_name_future = std::make_shared<Future<std::string>>();

    PerformProfileRequest([user_name_future, id = m_Id](const auto &reply) {
        std::string id_ = id;

        if(!reply) {
            user_name_future->Realize(std::move(id_));
            return;
        }

        if (reply->StatusCode != 200 || !reply->Body.has_value()) {
            user_name_future->Realize(std::move(id_));
            return;
        }
        
        const auto &response_data = reply->Body.value();
        
        user_name_future->Realize(response_data.DisplayName.value_or(std::move(id_)));
    });

    return user_name_future->GetHandle();
}

std::shared_ptr<core::future::Future<std::optional<std::string>>::Handle> User::AvatarUrl() const {
    auto avatar_url_future = std::make_shared<Future<std::optional<std::string>>>();

    PerformProfileRequest([avatar_url_future](const auto &reply) mutable {
        if(!reply) {
            avatar_url_future->Realize(std::nullopt);
            return;
        }

        if (reply->StatusCode != 200 || !reply->Body.has_value()) {
            avatar_url_future->Realize(std::nullopt);
            return;
        }

        auto response_data = reply->Body.value();
        
        avatar_url_future->Realize(std::move(response_data.AvatarUrl));
    });

    return avatar_url_future->GetHandle();
}

bool User::operator==(const User &other) const { return m_Id == other.m_Id; }

void User::PerformProfileRequest(std::function<void(const RequestReply&)> callback) const {
    using namespace services::matrix::requests::implementation::profile;
    using namespace services::matrix::requests::implementation::common;

    auto request = ProfileRequest(m_Id);

    m_RequestManager->Execute<Empty, ProfileRequestResponse, Error>(
        request, [callback](const auto &reply) {
            callback(reply);
        });
}

} // namespace epsilon::model