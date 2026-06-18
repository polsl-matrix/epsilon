#pragma once

#include "serialization_primitive.hpp"

#include <string>

namespace epsilon::services::matrix::serialization {

class ISerializationStrategy {
public:
    virtual std::string Serialize(SerializationPrimitive) const = 0;
};

}
