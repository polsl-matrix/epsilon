#include "serializer.hpp"

#include "iserializable.hpp"
#include "serialization_primitive.hpp"
#include "iserialization_strategy.hpp"

#include <memory>
#include <string>
#include <utility>

namespace epsilon::services::matrix::serialization {

Serializer::Serializer(std::unique_ptr<ISerializationStrategy>&& strategy) {
    SetSerializationStrategy(std::move(strategy));
}

std::string Serializer::Serialize(const ISerializable& serializable) const {
    return serializable.Serialize(m_Strategy);
}

void Serializer::SetSerializationStrategy(std::unique_ptr<ISerializationStrategy>&& strategy) {
    m_Strategy = std::move(strategy);
}

}
