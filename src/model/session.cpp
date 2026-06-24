#include "session.hpp"

#include "../services/matrix/requests/authenticated_request_manager.hpp"

#include "user.hpp"

#include <memory>
#include <string>
#include <utility>

namespace epsilon::model {

Session::Session(std::shared_ptr<RequestManager> request_manager)
    : m_RequestManager(std::move(request_manager)) {}

User Session::CurrentUser() const {
    return User(m_RequestManager, "guy"); // To be replaced by /whoami
}

} // namespace epsilon::model