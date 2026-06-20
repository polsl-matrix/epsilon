#pragma once

#include "deserializer.hpp"

#include "deserializable.hpp"
#include "iserialization_strategy.hpp"

#include <memory>

namespace epsilon::services::matrix::serialization {

template <std::derived_from<IDeserializationStrategy> TStrategy, typename... ConstructorArgs>
    requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
Deserializer Deserializer::Construct(ConstructorArgs &&...args) {
    return Deserializer(std::make_unique<TStrategy>(args...));
}

template<typename T>
    requires Deserializable<T>
T Deserializer::Deserialize(const std::string& serialized) const {
    auto primitive_representation = m_Strategy->Deserialize(serialized);
    return ::epsilon::services::matrix::serialization::Deserialize<T>(primitive_representation);
}

template <std::derived_from<IDeserializationStrategy> TStrategy,
            typename... ConstructorArgs>
    requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
void Deserializer::SetDeserializationStrategy(ConstructorArgs &&...args) {
    m_Strategy = std::make_unique<TStrategy>(args...);
}

}
