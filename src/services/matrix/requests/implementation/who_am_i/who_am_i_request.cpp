#include "who_am_i_request.hpp"
#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::who_am_i {

HttpMethod WhoAmIRequest::Method() const { return HttpMethod::GET; }

std::string WhoAmIRequest::Endpoint() const {
    return "/_matrix/client/v3/account/whoami";
}

} // namespace epsilon::services::matrix::requests::implementation::registration