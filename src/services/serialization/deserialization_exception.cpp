#include "deserialization_exception.hpp"

#include "serialization_primitive.hpp"

#include <format>
#include <stdexcept>
#include <string>
#include <utility>

namespace epsilon::services::matrix::serialization {

// DeserializationUnexpectedPrimitiveException implementation
DeserializationUnexpectedPrimitiveException::
    DeserializationUnexpectedPrimitiveException(
        SerializationPrimitive expected, SerializationPrimitive encountered)
    : std::runtime_error("Expected a different primitive than encountered "
                         "during deserialization"),
      m_Expected(std::move(expected)), m_Encountered(std::move(encountered)) {}

SerializationPrimitive
DeserializationUnexpectedPrimitiveException::Expected() const {
    return m_Expected;
}

SerializationPrimitive
DeserializationUnexpectedPrimitiveException::Encountered() const {
    return m_Encountered;
}

// DeserializationFieldNotFoundException implementation
DeserializationFieldNotFoundException::DeserializationFieldNotFoundException(std::string expected_field)
    : std::runtime_error(std::format("Expected {} field was not found", expected_field)), m_ExpectedField(std::move(expected_field)) {}

std::string DeserializationFieldNotFoundException::ExpectedField() const {
    return m_ExpectedField;
}

// DeserializationUnrecognizedFormatException implementation
DeserializationUnrecognizedFormatException::
    DeserializationUnrecognizedFormatException(std::string expected_format)
    : std::runtime_error(std::format("Deserialization failed because of an "
                                     "unrecognized format. Expected format: {}",
                                     expected_format)),
      m_ExpectedFormat(std::move(expected_format)) {}

std::string DeserializationUnrecognizedFormatException::ExpectedFormat() const {
    return m_ExpectedFormat;
}

} // namespace epsilon::services::matrix::serialization
