#include "login_request_body.hpp"

#include "../../../../serialization/serialization_primitive.hpp"

#include <string>
#include <unordered_map>
#include <utility>

using epsilon::services::matrix::serialization::RObject;
using epsilon::services::matrix::serialization::Object;
using epsilon::services::matrix::serialization::String;

namespace epsilon::services::matrix::requests::implementation::login {

LoginRequestBody::LoginRequestBody(std::string username, std::string password)
    : Username(std::move(username)), Password(std::move(password)) {}

serialization::SerializationPrimitive LoginRequestBody::GetPrimitiveRepresentation() const {
    return RObject( Object { {
        { "type", String { "m.login.password" } },
        { "identifier", Object { {
            { "type", String { "m.id.user" } },
            { "user", String { Username } }
        } } },
        { "password", String { Password } },
        { "initial_device_display_name", String { "Epsilon App" } }
    } } );
}

}
