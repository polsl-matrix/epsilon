#pragma once

#include "http_method.hpp"
#include "../../serialization/iserializable.hpp"

#include <concepts>
#include <optional>
#include <string>
#include <unordered_map>

namespace epsilon::services::matrix::requests {

template<class TBody, class TResult>
    requires std::derived_from<TBody, serialization::ISerializable>
class Request {
    std::optional<TBody> m_Body;

public:
    virtual HttpMethod Method() const = 0;
    virtual std::string Endpoint() const = 0;
    virtual std::unordered_map<std::string, std::string> AdditionalHeaders() const;

    void SetBody(std::optional<TBody> body);
    void SetBody(std::optional<TBody>&& body);
    std::optional<TBody> GetBody();
};

}
