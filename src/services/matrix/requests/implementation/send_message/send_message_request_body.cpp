#include "send_message_request_body.hpp"

#include "../../../../serialization/serialization_primitive.hpp"

#include <string>
#include <unordered_map>
#include <utility>

using epsilon::services::matrix::serialization::Object;
using epsilon::services::matrix::serialization::RObject;
using epsilon::services::matrix::serialization::String;

namespace epsilon::services::matrix::requests::implementation::send_message {

SendMessageRequestBody::SendMessageRequestBody(std::string body)
    : Body(std::move(body)) {}

serialization::SerializationPrimitive
SendMessageRequestBody::GetPrimitiveRepresentation() const {
    return RObject(Object{ { { "body", String(Body) } } });
}

} // namespace epsilon::services::matrix::requests::implementation::send_message
