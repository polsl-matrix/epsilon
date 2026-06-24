#pragma once

namespace epsilon::features::registration {

enum class RegistrationError {
    UsernameTaken,
    ReachedRequestLimit,
    RequestFailed,
    UnknownError
};

}