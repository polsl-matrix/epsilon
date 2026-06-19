#pragma once

#include "serialization_primitive.hpp"

#include <stdexcept>

namespace epsilon::services::matrix::serialization {

class DeserializationUnexpectedPrimitiveException : public std::runtime_error {
    SerializationPrimitive m_Expected;
    SerializationPrimitive m_Encountered;

public:
    DeserializationUnexpectedPrimitiveException(SerializationPrimitive expected, SerializationPrimitive encountered);

    SerializationPrimitive Expected() const;
    SerializationPrimitive Encountered() const;
};

class DeserializationUnrecognizedFormatException : public std::runtime_error {
    std::string m_ExpectedFormat;

public:
    DeserializationUnrecognizedFormatException(std::string expected_format);

    std::string ExpectedFormat() const;
};

}
