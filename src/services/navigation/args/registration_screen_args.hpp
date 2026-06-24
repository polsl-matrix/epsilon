#pragma once

#include "../../matrix/requests/request_manager.hpp"
#include "../inavigation_service.hpp"
#include <memory>

namespace epsilon::services::navigation::args {

struct RegistrationScreenArgs {
    std::shared_ptr<matrix::requests::RequestManager> request_manager;
    std::shared_ptr<INavigationService> navigation_service;
};

}