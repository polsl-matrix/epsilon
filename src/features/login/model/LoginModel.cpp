#include "LoginModel.hpp"

#include <string>

bool LoginModel::Authenticate(const std::string &email,
                              const std::string &password) {
    return email == "test" && password == "test";
}