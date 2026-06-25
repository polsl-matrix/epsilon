#include "home_presenter.hpp"

#include "../../../core/event/util/action.hpp"
#include "../../../services/navigation/args/login_screen_args.hpp"
#include "../../../services/navigation/inavigation_service.hpp"
#include "../../../services/navigation/screen.hpp"
#include "../../chat_room/presenter/chat_room_presenter.hpp"
#include "../model/home_model.hpp"
#include "contracts/ihome_view.hpp"
#include "contracts/room_dto.hpp"

#include <iostream>
#include <memory>
#include <utility>

using epsilon::services::navigation::Screen;
using epsilon::services::navigation::args::LoginScreenArgs;

namespace epsilon::features::home {

HomePresenter::HomePresenter(
    std::unique_ptr<IHomeView> view, std::unique_ptr<HomeModel> model,
    std::shared_ptr<INavigationService> navigation_service)
    : m_NavigationService(std::move(navigation_service)),
      m_View(std::move(view)), m_Model(std::move(model)) {
    m_Model->GetRooms()->Then([this](const HomeModel::RoomsResult &result) {
        if (!result.has_value()) {
            return;
        }

        const std::shared_ptr<std::vector<model::Room>> &rooms_ptr =
            result.value();
        if (!rooms_ptr) {
            return;
        }

        std::vector<RoomDto> view_dtos;
        view_dtos.reserve(rooms_ptr->size());

        for (const auto &room : *rooms_ptr) {
            view_dtos.push_back(RoomDto{ room.Id(), room.Name() });
        }

        m_View->SetRoomsList(view_dtos);
    });

    m_SelectRoomEventHandle =
        m_View->OnChatSelected.Attach<Action<std::string>>(
            [this](std::string room_id) {
                std::shared_ptr<chat_room::IChatRoomView> view = this->m_View->LoadChatRoomView();
                std::shared_ptr<model::Room> model = this->m_Model->SelectRoom(room_id);
                std::shared_ptr<model::Session> session = this->m_Model->GetSession();

                this->m_OpenRoom =
                    std::make_unique<chat_room::ChatRoomPresenter>(view, model, session);
            });

    m_LogoutEventHandle = m_View->OnLogoutRequested.Attach<Action<>>(
        [this] { this->HandleLogout(); });
}

void HomePresenter::HandleLogout() {
    const auto request_manager = m_Model->Logout();

    m_NavigationService->NavigateTo(
        Screen::Login,
        LoginScreenArgs{ std::move(request_manager), m_NavigationService });
}

} // namespace epsilon::features::home
