#pragma once

#include "../../../../core/event/event.hpp"

#include <string>

class ILoginView {
  public:
    virtual ~ILoginView() = default;
    virtual void ShowLoginError(const std::string &error) = 0;
    virtual void ShowLoginSuccess() = 0;

    epsilon::core::event::Event<std::string, std::string> OnLoginRequested;
};