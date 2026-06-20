#include "authenticated_request_manager.hpp"

#include "../../serialization/serializer.hpp"
#include "iraw_request_manager.hpp"
#include "request_manager.hpp"

#include <memory>

namespace epsilon::services::matrix::requests {

AuthenticatedRequestManager::AuthenticatedRequestManager(
    std::unique_ptr<RequestManager> &&inner, std::string token)
    : m_InnerManager(std::move(inner)), m_AccessToken(std::move(token)) {}

std::unique_ptr<RequestManager> AuthenticatedRequestManager::Release() && {
    return std::move(m_InnerManager);
}

} // namespace epsilon::services::matrix::requests
