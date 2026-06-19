#pragma once

#include "../serialization_primitive.hpp"
#include "../ideserialization_strategy.hpp"

#include <stdexcept>
#include <string>

#include <QJsonValue>

namespace epsilon::services::matrix::serialization::json {

class JsonDeserializationStrategy : public IDeserializationStrategy {
    SerializationPrimitive ConvertJsonValue(const QJsonValue& jsonValue) const;

public:
    virtual SerializationPrimitive Deserialize(const std::string&) const override;
};

}
