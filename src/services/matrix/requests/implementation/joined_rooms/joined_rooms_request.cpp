#include "joined_rooms_request.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::joined_rooms {

HttpMethod JoinedRoomsRequest::Method() const { return HttpMethod::GET; }

std::string JoinedRoomsRequest::Endpoint() const {
    return "/_matrix/client/v3/joined_rooms";
}

} // namespace epsilon::services::matrix::requests::implementation::joined_rooms