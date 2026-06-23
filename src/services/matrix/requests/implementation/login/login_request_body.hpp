#pragma once

#include "../../../../serialization/iserializable.hpp"
#include "../../../../serialization/serialization_primitive.hpp"

namespace epsilon::services::matrix::requests::implementation::login {

struct LoginRequestBody : public serialization::ISerializable {
    std::string Username;
    std::string Password;

    LoginRequestBody(std::string username, std::string password);

protected:
    virtual serialization::SerializationPrimitive GetPrimitiveRepresentation() const override;
};

}
