#include "profile_request.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::profile {

ProfileRequest::ProfileRequest(std::string user_id) : m_UserId(user_id) {}

HttpMethod ProfileRequest::Method() const { return HttpMethod::GET; }

std::string ProfileRequest::Endpoint() const {
    return "/_matrix/client/v3/profile/" + m_UserId;
}

} // namespace epsilon::services::matrix::requests::implementation::profile