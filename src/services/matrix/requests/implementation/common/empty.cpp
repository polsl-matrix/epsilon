#include "empty.hpp"

#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/iserializable.hpp"

using epsilon::services::matrix::serialization::Object;
using epsilon::services::matrix::serialization::RObject;

namespace epsilon::services::matrix::requests::implementation::common {

serialization::SerializationPrimitive
Empty::GetPrimitiveRepresentation() const {
    return RObject(Object{});
}

} // namespace epsilon::services::matrix::requests::implementation::common

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::common::Empty
Deserialize<requests::implementation::common::Empty>(SerializationPrimitive) {
    return requests::implementation::common::Empty{};
}

} // namespace epsilon::services::matrix::serialization
