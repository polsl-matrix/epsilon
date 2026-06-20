#include "request.hpp"

#include "../../serialization/iserializable.hpp"
#include "../../serialization/deserializable.hpp"

#include <utility>

namespace epsilon::services::matrix::requests {

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
std::unordered_map<std::string, std::string> Request<TBody, TResult, TError>::AdditionalHeaders() const {
    return {};
}

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
void Request<TBody, TResult, TError>::SetBody(const std::optional<TBody>& body) {
    m_Body = body;
}

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
void Request<TBody, TResult, TError>::SetBody(std::optional<TBody>&& body) {
    m_Body = std::move(body);
}

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
std::optional<TBody> Request<TBody, TResult, TError>::GetBody() const {
    return m_Body;
}

} // namespace epsilon::services::matrix::requests
