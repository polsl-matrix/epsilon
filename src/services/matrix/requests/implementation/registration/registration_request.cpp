#include "registration_request.hpp"
#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::registration {

HttpMethod RegistrationRequest::Method() const { return HttpMethod::POST; }

std::string RegistrationRequest::Endpoint() const {
    return "/_matrix/client/v3/register";
}

} // namespace epsilon::services::matrix::requests::implementation::registration