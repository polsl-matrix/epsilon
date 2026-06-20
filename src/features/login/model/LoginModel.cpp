#include "LoginModel.hpp"

#include <string>

bool LoginModel::Authenticate(
    const std::string
        &email, // NOLINT(readability-convert-member-functions-to-static)
    const std::string &password) {
    return email == "test" && password == "test";
}