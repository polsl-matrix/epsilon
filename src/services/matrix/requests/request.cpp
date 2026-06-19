#include "request.hpp"

#include <utility>

namespace epsilon::services::matrix::requests {

template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable>
std::unordered_map<std::string, std::string> Request<TBody, TResult>::AdditionalHeaders() const {
    return {};
}

template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable>
void Request<TBody, TResult>::SetBody(std::optional<TBody> body) {
    m_Body = body;
}

template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable>
void Request<TBody, TResult>::SetBody(std::optional<TBody>&& body) {
    m_Body = std::move(body);
}

template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable>
std::optional<TBody> Request<TBody, TResult>::GetBody() {
    return m_Body;
}

} // namespace epsilon::services::matrix::requests
