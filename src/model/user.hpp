#pragma once

#include "../services/matrix/requests/authenticated_request_manager.hpp"
#include "../services/matrix/requests/request_manager.hpp"
#include "../services/matrix/requests/implementation/profile/profile_request_response.hpp"
#include "../services/matrix/requests/implementation/common/error.hpp"
#include "../core/future/future.hpp"

#include <expected>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace epsilon::model {

class User {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;

    std::shared_ptr<RequestManager> m_RequestManager;

    std::string m_Id;

    using RequestReply = std::optional<services::matrix::requests::RequestManager::Reply<
        services::matrix::requests::implementation::profile::ProfileRequestResponse,
        services::matrix::requests::implementation::common::Error>>;

    void PerformProfileRequest(std::function<void(const RequestReply&)> callback) const;

public:
    User(std::shared_ptr<RequestManager> request_manager, std::string id);

    std::string Id() const;
    std::shared_ptr<core::future::Future<std::string>::Handle> Name() const;
    std::shared_ptr<core::future::Future<std::optional<std::string>>::Handle> AvatarUrl() const;

    bool operator==(const User& other) const;
};

}