#pragma once

#include <functional>

class IHomeView {
  public:
    virtual ~IHomeView() = default;
    virtual void ShowLogoutSuccess() = 0;

    std::function<void()> OnLogoutRequested;
};