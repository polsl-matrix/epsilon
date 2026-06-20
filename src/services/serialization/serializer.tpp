#pragma once

#include "serializer.hpp"

#include "iserialization_strategy.hpp"

#include <memory>

namespace epsilon::services::matrix::serialization {

template <std::derived_from<ISerializationStrategy> TStrategy, typename... ConstructorArgs>
    requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
Serializer Serializer::Construct(ConstructorArgs &&...args) {
    return Serializer(std::make_unique<TStrategy>(args...));
}

template <std::derived_from<ISerializationStrategy> TStrategy,
            typename... ConstructorArgs>
    requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
void Serializer::SetSerializationStrategy(ConstructorArgs &&...args) {
    m_Strategy = std::make_unique<TStrategy>(args...);
}

}
