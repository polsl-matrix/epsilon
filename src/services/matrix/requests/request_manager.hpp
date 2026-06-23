#pragma once

#include "iraw_request_manager.hpp"
#include "request.hpp"
#include "../../serialization/iserializable.hpp"
#include "../../serialization/deserializable.hpp"
#include "../../serialization/serializer.hpp"
#include "../../serialization/deserializer.hpp"

#include <concepts>
#include <expected>
#include <functional>
#include <memory>
#include <optional>

namespace epsilon::services::matrix::requests {

class RequestManager {
protected:
    std::string m_BaselineUrl;
    std::shared_ptr<IRawRequestManager> m_RawRequestManager;
    std::unique_ptr<serialization::Serializer> m_Serializer;
    std::shared_ptr<serialization::Deserializer> m_Deserializer;

public:
    // TODO: Add a builder for the RequestManager class
    RequestManager(
        std::string baseline_url,
        std::shared_ptr<IRawRequestManager>&& raw_request_manager,
        std::unique_ptr<serialization::Serializer>&& serializer,
        std::shared_ptr<serialization::Deserializer>&& deserializer
    );

    template<class TResult, class TError>
    struct Reply {
        int StatusCode;
        std::expected<TResult, TError> Body;
    };

    template<class TBody, class TResult, class TError>
        requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult> && serialization::Deserializable<TError>
    void Execute(const Request<TBody, TResult, TError>& request, std::function<void(std::optional<RequestManager::Reply<TResult, TError>>)> callback) const;

    std::string GetBaselineUrl() const;
};

}

#include "request_manager.tpp"
