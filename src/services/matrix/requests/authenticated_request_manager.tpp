#include "authenticated_request_manager.hpp"

#include "request_manager.hpp"
#include "iraw_request_manager.hpp"
#include "../../serialization/serializer.hpp"

#include <memory>

namespace epsilon::services::matrix::requests {

// AuthenticatedRequestProxy implementations
template<class TBody, class TResult>
AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult>::AuthenticatedRequestProxy(const Request<TBody, TResult>& req, std::string token)
: m_OriginalRequest(req), m_Token(std::move(token))
{
    this->SetBody(m_OriginalRequest.GetBody());
}

template<class TBody, class TResult>
HttpMethod AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult>::Method() const { return m_OriginalRequest.Method(); }

template<class TBody, class TResult>
std::string AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult>::Endpoint() const { return m_OriginalRequest.Endpoint(); }

template<class TBody, class TResult>
std::unordered_map<std::string, std::string> AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult>::AdditionalHeaders() const {
    auto user_headers = m_OriginalRequest.GetAdditionalHeaders();

    // If the request configures its own authorization, we let it
    if (user_headers.contains("Authorization")) {
        return user_headers;
    }

    user_headers["Authorization"] = std::format("Bearer {}", m_Token);

    return user_headers;
}

// AuthenticatedRequestManager implementations
template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable>
void AuthenticatedRequestManager::Execute(const Request<TBody, TResult>& request, std::function<void(TResult)> callback) const {
    AuthenticatedRequestProxy<TBody, TResult> auth_request(request, m_AccessToken);
    
    m_InnerManager.Execute(auth_request, callback);
}

}
