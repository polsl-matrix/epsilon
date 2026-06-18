#pragma once

#include "serialization_primitive.hpp"
#include "iserialization_strategy.hpp"

#include <memory>
#include <string>

namespace epsilon::services::matrix::serialization {

class ISerializable {
protected:
    virtual SerializationPrimitive GetPrimitiveRepresentation() const = 0;

public:
    virtual ~ISerializable() = default;

    std::string Serialize(const std::unique_ptr<ISerializationStrategy>& strategy) const;
};

}
