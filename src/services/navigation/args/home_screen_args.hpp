#pragma once

#include "../inavigation_service.hpp"
#include "../../matrix/requests/authenticated_request_manager.hpp"

namespace epsilon::services::navigation::args {

struct HomeScreenArgs {
    std::shared_ptr<matrix::requests::AuthenticatedRequestManager> AuthenticatedRequestManager;
    std::shared_ptr<INavigationService> NavigationService;
};

}
