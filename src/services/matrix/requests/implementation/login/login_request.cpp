#include "login_request.hpp"

#include "../../http_method.hpp"
#include "../../request.hpp"

namespace epsilon::services::matrix::requests::implementation::login {

HttpMethod LoginRequest::Method() const {
    return HttpMethod::POST;
}

std::string LoginRequest::Endpoint() const {
    return "/_matrix/client/v3/login";
}

};
