#pragma once

#include "../../../../serialization/iserializable.hpp"
#include "../../../../serialization/serialization_primitive.hpp"

namespace epsilon::services::matrix::requests::implementation::send_message {

struct SendMessageRequestBody : public serialization::ISerializable {
    std::string Body;

    SendMessageRequestBody(std::string body);

protected:
    virtual serialization::SerializationPrimitive GetPrimitiveRepresentation() const override;
};

}
