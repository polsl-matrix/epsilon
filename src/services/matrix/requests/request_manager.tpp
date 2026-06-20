#include "request_manager.hpp"

#include "request.hpp"
#include "raw_reply.hpp"
#include "raw_request.hpp"
#include "../../serialization/iserializable.hpp"

#include <concepts>
#include <expected>
#include <format>
#include <functional>
#include <optional>
#include <unordered_map>
#include <utility>

#include <iostream>

namespace epsilon::services::matrix::requests {

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
void RequestManager::Execute(const Request<TBody, TResult, TError>& request, std::function<void(std::optional<RequestManager::Reply<TResult, TError>>)> callback) const {
    std::unordered_map<std::string, std::string> request_headers = request.AdditionalHeaders();
    
    if (!request_headers.contains("Content-Type")) {
        request_headers["Content-Type"] = "Application/Json";
    }

    auto raw_request = RawRequest {
        request.Method(),
        std::format("{}/{}", m_BaselineUrl, request.Endpoint()),
        request.GetBody().transform([this](TBody body) { return this->m_Serializer->Serialize(body); }),
        request_headers
    };

    m_RawRequestManager->Execute(std::move(raw_request), [deserializer = this->m_Deserializer, callback](RawReply reply) {
        if(reply.StatusCode == 0) {
            callback(std::nullopt);
            return;
        }

        constexpr int http_status_ok = 200;
        constexpr int http_status_redirect = 300;

        if (reply.StatusCode >= http_status_ok && reply.StatusCode < http_status_redirect) {
            TResult deserialized = deserializer->Deserialize<TResult>(reply.Body.value_or(""));
            
            callback(Reply<TResult, TError> {
                reply.StatusCode,
                deserialized
            });
        } else {
            TError deserialized = deserializer->Deserialize<TError>(reply.Body.value_or(""));

            callback(Reply<TResult, TError> {
                reply.StatusCode,
                std::unexpected(deserialized)
            });
        }
    });
}

}
