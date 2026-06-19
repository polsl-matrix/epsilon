#pragma once

#include "serialization_primitive.hpp"

#include <string>

namespace epsilon::services::matrix::serialization {

class IDeserializationStrategy {
public:
    virtual SerializationPrimitive Deserialize(const std::string&) const = 0;
};

}
