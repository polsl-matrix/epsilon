#include "home_model.hpp"

#include "../../../model/room.hpp"
#include "../../../model/session.hpp"
#include "../../../services/matrix/requests/implementation/common/empty.hpp"
#include "../../../services/matrix/requests/implementation/common/error.hpp"
#include "../../../services/matrix/requests/implementation/logout/logout_request.hpp"
#include "../../../services/matrix/requests/implementation/joined_rooms/joined_rooms_request.hpp"
#include "../../../services/matrix/requests/implementation/joined_rooms/joined_rooms_request_response.hpp"
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

std::unique_ptr<model::Room>
HomeModel::SelectRoom(const std::string &room_id) const {
    return std::make_unique<model::Room>(m_RequestManager, room_id);
}

std::unique_ptr<model::Session> HomeModel::GetSession() const {
    return std::make_unique<model::Session>(m_RequestManager);
}

std::shared_ptr<typename core::future::Future<HomeModel::RoomsResult>::Handle> 
HomeModel::GetRooms() const {
    using namespace epsilon::services::matrix::requests::implementation::joined_rooms;
    using namespace epsilon::services::matrix::requests::implementation::common;

    auto rooms_future = std::make_shared<core::future::Future<RoomsResult>>();
    auto request = JoinedRoomsRequest();
    request.SetBody(Empty{});

    m_RequestManager->Execute<Empty, JoinedRoomsRequestResponse, Error>(
        request, [request_manager = m_RequestManager, rooms_future](auto reply) {
            if (!reply.has_value()) {
                rooms_future->Realize(std::unexpected(GetRoomsError::RequestFailed));
                return;
            }

            if (reply->StatusCode != 200 || !reply->Body.has_value()) {
                rooms_future->Realize(std::unexpected(GetRoomsError::UnknownError));
                return;
            }

            const auto& response_data = reply->Body.value();
            
            auto rooms_ptr = std::make_shared<std::vector<model::Room>>();
            rooms_ptr->reserve(response_data.JoinedRooms.size());

            for (const auto& id : response_data.JoinedRooms) {
                rooms_ptr->emplace_back(request_manager, id);
            }

            rooms_future->Realize(std::move(rooms_ptr));
        });

    return rooms_future->GetHandle();
}

std::shared_ptr<RequestManager_> HomeModel::Logout() {
    m_RequestManager->Execute<Empty, Empty, Error>(LogoutRequest(),
                                                   [](auto) {});

    return m_RequestManager->GetInner();
}

} // namespace epsilon::features::home
