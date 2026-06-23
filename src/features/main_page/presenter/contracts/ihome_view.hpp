#pragma once

#include <functional>

namespace epsilon::features::home {

class IHomeView {
  public:
    virtual ~IHomeView() = default;
    virtual void ShowLogoutSuccess() = 0;

    std::function<void()> OnLogoutRequested;
};

}
