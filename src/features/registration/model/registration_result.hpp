#pragma once

#include <string>

namespace epsilon::features::registration {

struct RegistrationResult {
    std::string AccessToken;
    std::string RefreshToken;
    std::string UserId;
};

}