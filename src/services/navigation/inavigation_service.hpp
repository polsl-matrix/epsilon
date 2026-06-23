#pragma once

#include "screen.hpp"
#include "../../features/base/ipresenter.hpp"

#include <any>

namespace epsilon::services::navigation {

class INavigationService {
  public:
    virtual ~INavigationService() = default;

    virtual void NavigateTo(Screen screen, std::any args = {}) = 0;
};

}
