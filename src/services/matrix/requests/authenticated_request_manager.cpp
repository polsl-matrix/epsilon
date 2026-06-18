#include "authenticated_request_manager.hpp"

#include "request_manager.hpp"
#include "iraw_request_manager.hpp"
#include "../../serialization/serializer.hpp"

#include <memory>

namespace epsilon::services::matrix::requests {

// AuthenticatedRequestManager implementations
AuthenticatedRequestManager::AuthenticatedRequestManager(RequestManager&& inner, std::string token)
    : m_InnerManager(std::move(inner)), m_AccessToken(std::move(token)) {}

AuthenticatedRequestManager AuthenticatedRequestManager::FromRequestManager(RequestManager&& request_manager, std::string access_token) {
    return AuthenticatedRequestManager(std::move(request_manager), std::move(access_token));
}

RequestManager AuthenticatedRequestManager::Release() && {
    return std::move(m_InnerManager);
}

}
