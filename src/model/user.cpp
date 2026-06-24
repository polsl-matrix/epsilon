#include "user.hpp"

#include "../services/matrix/requests/authenticated_request_manager.hpp"

#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace epsilon::model {

User::User(std::shared_ptr<RequestManager> request_manager, std::string id)
    : m_RequestManager(std::move(request_manager)), m_Id(std::move(id)) {}

std::string User::Id() const {
    return m_Id;
}

std::string User::Name() const {
    if(m_Id == "joker") {
        return "Joe Kerr";
    } else if(m_Id == "man") {
        return "Guy";
    } else {
        return "Anonymous";
    }
}

std::string User::AvatarUrl() const {
    return "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ43GBOA_SEHZbLwgJ-FOi713lFqgHCKXuTwbjRPNsZjPRFTIaSFhVWntg";
}

bool User::operator==(const User& other) const {
    return m_Id == other.m_Id;
}

}