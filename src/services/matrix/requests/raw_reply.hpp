#pragma once

#include <optional>
#include <string>

namespace epsilon::services::matrix::requests {

struct RawReply {
    int StatusCode;
    std::optional<std::string> Body;
};

}
