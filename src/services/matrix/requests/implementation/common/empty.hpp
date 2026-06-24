#pragma once

#include "../../../../serialization/iserializable.hpp"
#include "../../../../serialization/deserializable.hpp"

namespace epsilon::services::matrix::requests::implementation::common {

struct Empty : public serialization::ISerializable {
protected:
    virtual serialization::SerializationPrimitive GetPrimitiveRepresentation() const override;
};

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::common::Empty Deserialize<requests::implementation::common::Empty>(SerializationPrimitive primitive);

}
