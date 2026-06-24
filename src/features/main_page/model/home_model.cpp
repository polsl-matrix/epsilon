#include "home_model.hpp"

#include "../../../services/matrix/requests/implementation/common/empty.hpp"
#include "../../../services/matrix/requests/implementation/common/error.hpp"
#include "../../../services/matrix/requests/implementation/logout/logout_request.hpp"
#include "../../../services/matrix/requests/request_manager.hpp"

#include <memory>
#include <optional>
#include <utility>

using RequestManager_ = epsilon::services::matrix::requests::RequestManager;
using epsilon::services::matrix::requests::implementation::common::Empty;
using epsilon::services::matrix::requests::implementation::common::Error;
using epsilon::services::matrix::requests::implementation::logout::
    LogoutRequest;

namespace epsilon::features::home {

HomeModel::HomeModel(std::shared_ptr<RequestManager> request_manager)
    : m_RequestManager(std::move(request_manager)) {}

std::shared_ptr<RequestManager_> HomeModel::Logout() {
    m_RequestManager->Execute<Empty, Empty, Error>(LogoutRequest(),
                                                   [](auto) {});

    return m_RequestManager->GetInner();
}

} // namespace epsilon::features::home
