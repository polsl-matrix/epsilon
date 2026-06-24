#include "registration_request_body.hpp"
#include "../../../../serialization/serialization_primitive.hpp"

#include <string>
#include <utility>

using epsilon::services::matrix::serialization::Object;
using epsilon::services::matrix::serialization::RObject;
using epsilon::services::matrix::serialization::String;

namespace epsilon::services::matrix::requests::implementation::registration {

RegistrationRequestBody::RegistrationRequestBody(std::string username, std::string password)
    : Username(std::move(username)), Password(std::move(password)) {}

serialization::SerializationPrimitive
RegistrationRequestBody::GetPrimitiveRepresentation() const {
    return RObject(Object{
        { { "username", String{ Username } },
          { "password", String{ Password } } }
    });
}

}