#include "request_manager.hpp"

#include "request.hpp"
#include "raw_request.hpp"
#include "../../serialization/iserializable.hpp"

#include <concepts>
#include <format>
#include <unordered_map>

namespace epsilon::services::matrix::requests {

template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable>
TResult RequestManager::Execute(const Request<TBody, TResult>& request) const {
    auto raw_request = RawRequest {
        request.Method,
        std::format("{}/{}", m_BaselineUrl, request.Endpoint),
        request.GetBody().transform([&m_Serializer](TBody body) { return m_Serializer.Serialize(body); }),
        std::unordered_map<> {
            { "Content-Type": "Application/Json" }
        }
    };

    auto result = m_RawRequestManager.Execute(raw_request);

    // TODO: Deserialize the result and return the value
}

}
