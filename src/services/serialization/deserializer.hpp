#pragma once

#include "deserializable.hpp"
#include "serialization_primitive.hpp"
#include "ideserialization_strategy.hpp"

#include <memory>
#include <string>

namespace epsilon::services::matrix::serialization {

class Deserializer {
    std::unique_ptr<IDeserializationStrategy> m_Strategy;

public:
    Deserializer(std::unique_ptr<IDeserializationStrategy>&& strategy);
    template <std::derived_from<IDeserializationStrategy> TStrategy,
              typename... ConstructorArgs>
        requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
    static Deserializer Construct(ConstructorArgs &&...args);

    template<typename T>
        requires Deserializable<T>
    T Deserialize(const std::string& serialized) const;

    void SetDeserializationStrategy(std::unique_ptr<IDeserializationStrategy>&& strategy);
    template <std::derived_from<IDeserializationStrategy> TStrategy,
              typename... ConstructorArgs>
        requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
    void SetDeserializationStrategy(ConstructorArgs &&...args);
};

}

#include "deserializer.tpp"
