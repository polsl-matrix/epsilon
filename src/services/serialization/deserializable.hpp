#pragma once

#include "serialization_primitive.hpp"

namespace epsilon::services::matrix::serialization {

template<typename T>
T Deserialize(SerializationPrimitive serialized);

template<typename T>
concept Deserializable = requires(SerializationPrimitive primitive) {
    { Deserialize<T>(primitive) } -> std::same_as<T>;
};

}
