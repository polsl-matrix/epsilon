#include "deserializer.hpp"

#include "ideserialization_strategy.hpp"

#include <memory>
#include <utility>

namespace epsilon::services::matrix::serialization {

Deserializer::Deserializer(std::unique_ptr<IDeserializationStrategy> &&strategy)
    : m_Strategy(std::move(strategy)) {}

void Deserializer::SetDeserializationStrategy(
    std::unique_ptr<IDeserializationStrategy> &&strategy) {
    m_Strategy = std::move(strategy);
}

} // namespace epsilon::services::matrix::serialization
