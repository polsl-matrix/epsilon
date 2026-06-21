#include "error.hpp"

#include "../../../../serialization/deserializable.hpp"
#include "../../../../serialization/deserialization_helpers.hpp"

#include <optional>
#include <string>
#include <utility>
#include <variant>

using epsilon::services::matrix::serialization::Expect;
using epsilon::services::matrix::serialization::ReadField;

namespace epsilon::services::matrix::requests::implementation::common {

Error::Error(std::string error_code, std::optional<std::string> error_message) : m_ErrorCode(std::move(error_code)), m_ErrorMessage(std::move(error_message)) {}

std::string Error::ErrorCode() const {
    return m_ErrorCode;
}

std::optional<std::string> Error::ErrorMessage() const {
    return m_ErrorMessage;
}

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::common::Error Deserialize<requests::implementation::common::Error>(SerializationPrimitive primitive) {
    const auto reply = Expect<RObject>(primitive).get();

    const auto error_code = ReadField<String>(reply, "errcode");
    const auto error_message = ReadFieldOptional<String>(reply, "error");

    return requests::implementation::common::Error(
        error_code.value,
        error_message.transform([](const auto& error_message) { return error_message.value; })
    );
}

}
