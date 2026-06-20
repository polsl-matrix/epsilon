#pragma once

#include "http_method.hpp"

#include <optional>
#include <string>
#include <unordered_map>

namespace epsilon::services::matrix::requests {

struct RawRequest {
    HttpMethod Method;
    std::string Url;
    std::optional<std::string> Body;
    std::unordered_map<std::string, std::string> Headers;
};

}
