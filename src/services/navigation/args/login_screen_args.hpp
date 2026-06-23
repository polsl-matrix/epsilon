#pragma once

#include "../inavigation_service.hpp"
#include "../../matrix/requests/request_manager.hpp"

namespace epsilon::services::navigation::args {

struct LoginScreenArgs {
    std::shared_ptr<matrix::requests::RequestManager> RequestManager;
    std::shared_ptr<INavigationService> NavigationService;
};

}
