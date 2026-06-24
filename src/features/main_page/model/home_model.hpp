#pragma once

#include "../../../services/matrix/requests/authenticated_request_manager.hpp"
#include "../../../services/matrix/requests/request_manager.hpp"
#include "../../../model/room.hpp"
#include "../../../model/session.hpp"
#include "../../../core/future/future.hpp"

#include <memory>
#include <string>
#include <vector>
#include <expected>

namespace epsilon::features::home {

enum class GetRoomsError {
    RequestFailed,
    UnknownError
};

class HomeModel {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;
  
    std::shared_ptr<RequestManager> m_RequestManager;

  public:
    using RoomsResult = std::expected<std::shared_ptr<std::vector<model::Room>>, GetRoomsError>;

    HomeModel(std::shared_ptr<RequestManager> request_manager);

    std::shared_ptr<typename core::future::Future<RoomsResult>::Handle> GetRooms() const;
    std::unique_ptr<model::Room> SelectRoom(const std::string& room_id) const;
    std::unique_ptr<model::Session> GetSession() const;

    std::shared_ptr<services::matrix::requests::RequestManager> Logout();
};

}
