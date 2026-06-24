#pragma once

#include "../../../../serialization/iserializable.hpp"
#include "../../../../serialization/serialization_primitive.hpp"
#include <string>

namespace epsilon::services::matrix::requests::implementation::registration {

struct RegistrationRequestBody : public serialization::ISerializable {
    std::string Username;
    std::string Password;

    RegistrationRequestBody(std::string username, std::string password);

protected:
    virtual serialization::SerializationPrimitive GetPrimitiveRepresentation() const override;
};

}