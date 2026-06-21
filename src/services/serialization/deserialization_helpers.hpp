#pragma once

#include "serialization_primitive.hpp"

#include "../../util/alternative_of/alternative_of.hpp"

#include <optional>
#include <string>

namespace epsilon::services::matrix::serialization {

template<util::alternative_of<SerializationPrimitive> TPrimitive>
TPrimitive Expect(const SerializationPrimitive& primitive);

template<util::alternative_of<SerializationPrimitive> TField>
TField ReadField(const Object& object, const std::string& field_name);

template<util::alternative_of<SerializationPrimitive> TField>
std::optional<TField> ReadFieldOptional(const Object& object, const std::string& field_name);

}

#include "deserialization_helpers.tpp"
