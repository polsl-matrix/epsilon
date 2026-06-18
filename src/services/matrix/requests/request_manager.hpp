#pragma once

#include "iraw_request_manager.hpp"
#include "request.hpp"
#include "../../serialization/iserializable.hpp"
#include "../../serialization/serializer.hpp"

#include <concepts>
#include <memory>

namespace epsilon::services::matrix::requests {

class RequestManager {
protected:
    std::string m_BaselineUrl;
    std::unique_ptr<IRawRequestManager> m_RawRequestManager;
    std::unique_ptr<serialization::Serializer> m_Serializer;

public:
    RequestManager(
        std::string baseline_url,
        std::unique_ptr<IRawRequestManager>&& raw_request_manager,
        std::unique_ptr<serialization::Serializer>&& serializer
    );

    template<class TBody, class TResult>
        requires std::derived_from<TBody, serialization::ISerializable>
    TResult Execute(const Request<TBody, TResult>& request) const;

    std::string GetBaselineUrl() const;
};

}

#include "request_manager.tpp"
