#pragma once

#include "raw_request.hpp"
#include "../../serialization/serialization_primitive.hpp"

namespace epsilon::services::matrix::requests {

class IRawRequestManager {
public:
    virtual serialization::SerializationPrimitive Execute(RawRequest&& request) const = 0;
};

}
