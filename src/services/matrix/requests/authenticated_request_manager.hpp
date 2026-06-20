#pragma once

#include "request_manager.hpp"
#include "request.hpp"
#include "../../serialization/iserializable.hpp"
#include "../../serialization/serializer.hpp"

#include <concepts>
#include <memory>

namespace epsilon::services::matrix::requests {

class AuthenticatedRequestManager {
private:
    std::unique_ptr<RequestManager> m_InnerManager;
    std::string m_AccessToken;

    template<class TBody, class TResult, class TError>
        requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
    class AuthenticatedRequestProxy : public Request<TBody, TResult, TError> {
    private:
        const Request<TBody, TResult, TError>& m_OriginalRequest;
        std::string m_Token;
    public:
        AuthenticatedRequestProxy(const Request<TBody, TResult, TError>& request, std::string token);

        HttpMethod Method() const override;
        std::string Endpoint() const override;
        std::unordered_map<std::string, std::string> AdditionalHeaders() const override;
    };

public:
    AuthenticatedRequestManager(std::unique_ptr<RequestManager>&& inner, std::string token);

    std::unique_ptr<RequestManager> Release() &&;

    template<class TBody, class TResult, class TError>
        requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
    void Execute(const Request<TBody, TResult, TError>& request, std::function<void(std::optional<RequestManager::Reply<TResult, TError>>)> callback) const;
};

}

#include "authenticated_request_manager.tpp"
