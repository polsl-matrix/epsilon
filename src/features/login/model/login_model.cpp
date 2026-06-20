#include "login_model.hpp"

#include <string>

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool LoginModel::Authenticate(const std::string &email,
                              const std::string &password) {
    return email == "test" && password == "test";
}