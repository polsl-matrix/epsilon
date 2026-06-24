#pragma once

#include "../../../services/matrix/requests/authenticated_request_manager.hpp"
#include "../../../services/matrix/requests/request_manager.hpp"
#include "../../../model/room.hpp"
#include "../../../model/session.hpp"

#include <memory>

namespace epsilon::features::home {

class HomeModel {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;
  
    std::shared_ptr<RequestManager> m_RequestManager;

  public:
    HomeModel(std::shared_ptr<RequestManager> request_manager);

    std::unique_ptr<model::Room> SelectRoom(const std::string& room_id) const;
    std::unique_ptr<model::Session> GetSession() const;

    std::shared_ptr<services::matrix::requests::RequestManager> Logout();
};

}
