#pragma once

#include "../serialization_primitive.hpp"
#include "../iserialization_strategy.hpp"

#include <string>

namespace epsilon::services::matrix::serialization::json {

class JsonSerializationStrategy : public ISerializationStrategy {
public:
    virtual std::string Serialize(SerializationPrimitive primitive) const override;
};

}
