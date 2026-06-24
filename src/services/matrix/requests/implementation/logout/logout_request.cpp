#include "logout_request.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::logout {

HttpMethod LogoutRequest::Method() const { return HttpMethod::POST; }

std::string LogoutRequest::Endpoint() const {
    return "/_matrix/client/v3/logout";
}

}; // namespace epsilon::services::matrix::requests::implementation::logout
