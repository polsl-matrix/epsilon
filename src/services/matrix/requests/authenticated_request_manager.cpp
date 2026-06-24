#include "authenticated_request_manager.hpp"

#include "request_manager.hpp"

#include <memory>
#include <string>
#include <utility>

namespace epsilon::services::matrix::requests {

AuthenticatedRequestManager::AuthenticatedRequestManager(
    std::shared_ptr<RequestManager> inner, std::string token)
    : m_InnerManager(std::move(inner)), m_AccessToken(std::move(token)) {}

std::shared_ptr<RequestManager> AuthenticatedRequestManager::GetInner() {
    return m_InnerManager;
}

std::string AuthenticatedRequestManager::UserId() const {
    return "man";
}

} // namespace epsilon::services::matrix::requests
