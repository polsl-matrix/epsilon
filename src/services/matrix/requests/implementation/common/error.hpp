#pragma once

#include "../../../../serialization/deserializable.hpp"

#include <string>
#include <optional>

namespace epsilon::services::matrix::requests::implementation::common {

class Error {
    std::string m_ErrorCode;
    std::optional<std::string> m_ErrorMessage;

public:
    Error(std::string error_code, std::optional<std::string> error_message = std::nullopt);

    std::string ErrorCode() const;
    std::optional<std::string> ErrorMessage() const;
};

}

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::common::Error Deserialize<requests::implementation::common::Error>(SerializationPrimitive primitive);

}
