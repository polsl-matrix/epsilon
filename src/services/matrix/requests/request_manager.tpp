#include "request_manager.hpp"

#include "request.hpp"
#include "raw_reply.hpp"
#include "raw_request.hpp"
#include "../../serialization/iserializable.hpp"

#include <concepts>
#include <format>
#include <iostream>
#include <unordered_map>
#include <utility>

namespace epsilon::services::matrix::requests {

template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult>
void RequestManager::Execute(const Request<TBody, TResult>& request, std::function<void(TResult)> callback) const {
    auto raw_request = RawRequest {
        request.Method,
        std::format("{}/{}", m_BaselineUrl, request.Endpoint),
        request.GetBody().transform([this](TBody body) { return this->m_Serializer->Serialize(body); }),
        std::unordered_map<std::string, std::string> {
            { "Content-Type", "Application/Json" }
        }
    };

    m_RawRequestManager->Execute(std::move(raw_request), [this, callback](RawReply reply) {
        if(reply.StatusCode >= 200 && reply.StatusCode < 300) {
            TResult deserialized = this->m_Deserializer->Deserialize<TResult>(reply.Body);

            callback();
        } else {
            std::cerr << "TODO: Implement error handling for HTTP requests\n";
        }
    });
}

}
