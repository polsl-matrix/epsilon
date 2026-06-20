#include "request_manager.hpp"

#include "iraw_request_manager.hpp"
#include "../../serialization/serializer.hpp"

#include <memory>
#include <utility>

namespace epsilon::services::matrix::requests {

RequestManager::RequestManager(
    std::string baseline_url,
    std::unique_ptr<IRawRequestManager>&& raw_request_manager,
    std::unique_ptr<serialization::Serializer>&& serializer,
    std::shared_ptr<serialization::Deserializer>&& deserializer
) : m_BaselineUrl(std::move(baseline_url)),
    m_RawRequestManager(std::move(raw_request_manager)),
    m_Serializer(std::move(serializer)),
    m_Deserializer(std::move(deserializer)) {}


std::string RequestManager::GetBaselineUrl() const {
    return m_BaselineUrl;
}

}
