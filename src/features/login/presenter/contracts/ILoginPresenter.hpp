#pragma once

#include <string>

class ILoginPresenter {
public:
    virtual ~ILoginPresenter() = default;
    virtual void HandleLogin(const std::string& email, const std::string& password) = 0;
};