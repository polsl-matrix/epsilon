#pragma once

#include "iserializable.hpp"
#include "serialization_primitive.hpp"
#include "iserialization_strategy.hpp"

#include <memory>
#include <string>

namespace epsilon::services::matrix::serialization {

class Serializer {
    std::unique_ptr<ISerializationStrategy> m_Strategy;

public:
    Serializer(std::unique_ptr<ISerializationStrategy>&& strategy);
    template <std::derived_from<ISerializationStrategy> TStrategy,
              typename... ConstructorArgs>
        requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
    static Serializer Construct(ConstructorArgs &&...args);

    std::string Serialize(const ISerializable& serializable) const;

    void SetSerializationStrategy(std::unique_ptr<ISerializationStrategy>&& strategy);
    template <std::derived_from<ISerializationStrategy> TStrategy,
              typename... ConstructorArgs>
        requires std::is_constructible_v<TStrategy, ConstructorArgs &&...>
    void SetSerializationStrategy(ConstructorArgs &&...args);
};

}

#include "serializer.tpp"
