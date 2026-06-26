#pragma once

#include "deserialization_helpers.hpp"

#include "deserialization_exception.hpp"
#include "serialization_primitive.hpp"

#include "../../util/alternative_of/alternative_of.hpp"

#include <optional>
#include <string>

namespace epsilon::services::matrix::serialization {

template<util::alternative_of<SerializationPrimitive> TPrimitive>
TPrimitive Expect(const SerializationPrimitive& primitive) {
    if (!std::holds_alternative<TPrimitive>(primitive)) {
        throw DeserializationUnexpectedPrimitiveException(TPrimitive{}, primitive);
    }

    return std::get<TPrimitive>(primitive);
}

template<util::alternative_of<SerializationPrimitive> TField>
TField ReadField(const Object& object, const std::string& field_name) {
    if(!object.values.contains(field_name)) {
        throw DeserializationFieldNotFoundException(field_name);
    }

    const auto &field = object.values.at(field_name);

    return Expect<TField>(field);
}

template<util::alternative_of<SerializationPrimitive> TField>
std::optional<TField> ReadFieldOptional(const Object& object, const std::string& field_name) {
    if(!object.values.contains(field_name)) {
        return std::nullopt;
    }

    const auto &field = object.values.at(field_name);

    try {
        return Expect<TField>(field);
    } catch(const DeserializationUnexpectedPrimitiveException& error) {
        return std::nullopt;
    }
}

}
