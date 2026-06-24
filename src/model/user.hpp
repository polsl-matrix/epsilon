#pragma once

#include "../services/matrix/requests/authenticated_request_manager.hpp"

#include <memory>
#include <optional>
#include <string>

namespace epsilon::model {

class User {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;

    std::shared_ptr<RequestManager> m_RequestManager;

    std::string m_Id;

public:
    User(std::shared_ptr<RequestManager> request_manager, std::string id);

    std::string Id() const;
    std::string Name() const;
    std::string AvatarUrl() const;

    bool operator==(const User& other) const;
};

}