#pragma once

#include "iraw_request_manager.hpp"
#include "request.hpp"
#include "../../serialization/iserializable.hpp"
#include "../../serialization/deserializable.hpp"
#include "../../serialization/serializer.hpp"
#include "../../serialization/deserializer.hpp"

#include <concepts>
#include <functional>
#include <memory>

namespace epsilon::services::matrix::requests {

class RequestManager {
protected:
    std::string m_BaselineUrl;
    std::unique_ptr<IRawRequestManager> m_RawRequestManager;
    std::unique_ptr<serialization::Serializer> m_Serializer;
    std::unique_ptr<serialization::Deserializer> m_Deserializer;

public:
    RequestManager(
        std::string baseline_url,
        std::unique_ptr<IRawRequestManager>&& raw_request_manager,
        std::unique_ptr<serialization::Serializer>&& serializer,
        std::unique_ptr<serialization::Deserializer>&& deserializer
    );

    // TODO: Add another generic argument for a TBody when the server returns an error
    // We'll also probably have to return something more than a bare TResult
    // like a custom Reply<TResult, TError> class, which would also provide a status code
    // and make the result a std::expected with TError on the other side.
    template<class TBody, class TResult>
        requires std::derived_from<TBody, serialization::ISerializable> && serialization::Deserializable<TResult>
    void Execute(const Request<TBody, TResult>& request, std::function<void(TResult)> callback) const;

    std::string GetBaselineUrl() const;
};

}

#include "request_manager.tpp"
