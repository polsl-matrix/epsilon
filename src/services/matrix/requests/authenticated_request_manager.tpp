#pragma once

#include "authenticated_request_manager.hpp"

#include "request_manager.hpp"
#include "iraw_request_manager.hpp"
#include "../../serialization/serializer.hpp"

#include <memory>

namespace epsilon::services::matrix::requests {

// AuthenticatedRequestProxy implementations
template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult, TError>::AuthenticatedRequestProxy(const Request<TBody, TResult, TError>& request, std::string token)
    : m_OriginalRequest(request), m_Token(std::move(token))
{
    this->SetBody(m_OriginalRequest.GetBody());
}

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
HttpMethod AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult, TError>::Method() const { return m_OriginalRequest.Method(); }

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
std::string AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult, TError>::Endpoint() const { return m_OriginalRequest.Endpoint(); }

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
std::unordered_map<std::string, std::string> AuthenticatedRequestManager::AuthenticatedRequestProxy<TBody, TResult, TError>::AdditionalHeaders() const {
    auto user_headers = m_OriginalRequest.AdditionalHeaders();

    // If the request configures its own authorization, we let it
    if (user_headers.contains("Authorization")) {
        return user_headers;
    }

    user_headers["Authorization"] = std::format("Bearer {}", m_Token);

    return user_headers;
}

// AuthenticatedRequestManager implementations
template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
void AuthenticatedRequestManager::Execute(const Request<TBody, TResult, TError>& request, std::function<void(std::optional<RequestManager::Reply<TResult, TError>>)> callback) const {
    AuthenticatedRequestProxy<TBody, TResult, TError> auth_request(request, m_AccessToken);
    
    m_InnerManager->Execute(auth_request, std::move(callback));
}

}
