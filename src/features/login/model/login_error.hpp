#pragma once

namespace epsilon::features::login {

enum class LoginError {
    IncorrectAuthenticationData,
    UserDeactivated,
    ReachedRequestLimit,
    RequestFailed,
    UnknownError
};

}
