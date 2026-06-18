#pragma once

#include <string>

class LoginModel {
public:
    bool Authenticate(const std::string& email, const std::string& password);
};