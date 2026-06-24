#pragma once

#include "../../../../serialization/deserializable.hpp"

#include <string>
#include <vector>

namespace epsilon::services::matrix::requests::implementation::joined_rooms {

struct JoinedRoomsRequestResponse {
    std::vector<std::string> JoinedRooms;
};

} // namespace epsilon::services::matrix::requests::implementation::joined_rooms

namespace epsilon::services::matrix::serialization {

template <>
requests::implementation::joined_rooms::JoinedRoomsRequestResponse 
Deserialize<requests::implementation::joined_rooms::JoinedRoomsRequestResponse>(SerializationPrimitive primitive);

} // namespace epsilon::services::matrix::serialization