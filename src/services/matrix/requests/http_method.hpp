#pragma once

#include <cstdint>

namespace epsilon::services::matrix::requests {

enum class HttpMethod: std::uint8_t {
    GET,
    POST,
    PUT
};

} // namespace epsilon::services::matrix::requests