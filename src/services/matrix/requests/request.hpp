#pragma once

#include "http_method.hpp"
#include "../../serialization/iserializable.hpp"
#include "../../serialization/deserializable.hpp"

#include <concepts>
#include <optional>
#include <string>
#include <unordered_map>

namespace epsilon::services::matrix::requests {

template<class TBody, class TResult, class TError>
    requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
class Request {
    std::optional<TBody> m_Body;

public:
    Request(std::optional<TBody> body = std::nullopt);

    virtual HttpMethod Method() const = 0;
    virtual std::string Endpoint() const = 0;
    virtual std::unordered_map<std::string, std::string> AdditionalHeaders() const;

    void SetBody(const std::optional<TBody>& body);
    void SetBody(std::optional<TBody>&& body);
    std::optional<TBody> GetBody() const;
};

}

#include "request.tpp"
