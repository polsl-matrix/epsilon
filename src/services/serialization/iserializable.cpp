#include "iserializable.hpp"

#include "iserialization_strategy.hpp"

#include <memory>
#include <string>

namespace epsilon::services::matrix::serialization {

std::string ISerializable::Serialize(const std::unique_ptr<ISerializationStrategy>& strategy) const {
    const auto primitive_representation = GetPrimitiveRepresentation();

    return strategy->Serialize(primitive_representation);
}

}
