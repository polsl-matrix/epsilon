#pragma once

#include <string>

class ILoginView {
  public:
    virtual ~ILoginView() = default;
    virtual void ShowLoginError(const std::string &error) = 0;
    virtual void ShowLoginSuccess() = 0;
};