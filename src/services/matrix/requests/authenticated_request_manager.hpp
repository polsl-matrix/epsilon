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
    RequestManager m_InnerManager;
    std::string m_AccessToken;

    template<class TBody, class TResult>
    class AuthenticatedRequestProxy : public Request<TBody, TResult> {
    private:
        const Request<TBody, TResult>& m_OriginalRequest;
        std::string m_Token;
    public:
        AuthenticatedRequestProxy(const Request<TBody, TResult>& req, std::string token);

        HttpMethod Method() const override;
        std::string Endpoint() const override;
        std::unordered_map<std::string, std::string> AdditionalHeaders() const override;
    };

public:
    AuthenticatedRequestManager(RequestManager&& inner, std::string token);

    static AuthenticatedRequestManager FromRequestManager(RequestManager&& request_manager, std::string access_token);
    RequestManager Release() &&;

    template<class TBody, class TResult>
        requires std::derived_from<TBody, serialization::ISerializable>
    void Execute(const Request<TBody, TResult>& request, std::function<void(TResult)> callback) const;
};

}

#include "authenticated_request_manager.tpp"
