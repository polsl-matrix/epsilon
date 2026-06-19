#pragma once

#include "raw_reply.hpp"
#include "raw_request.hpp"

#include <functional>

namespace epsilon::services::matrix::requests {

class IRawRequestManager {
public:
    virtual void Execute(RawRequest&& request, std::function<void(RawReply)> callback) = 0;
};

}
