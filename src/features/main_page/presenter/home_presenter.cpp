#include "home_presenter.hpp"

#include "../../../core/event/util/action.hpp"
#include "../../../services/navigation/args/login_screen_args.hpp"
#include "../../../services/navigation/inavigation_service.hpp"
#include "../../../services/navigation/screen.hpp"
#include "../model/home_model.hpp"
#include "contracts/ihome_view.hpp"

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
    m_SelectRoomEventDetachment = m_View->OnChatSelected.Attach(
        std::make_shared<core::event::util::Action<std::string>>(
            [this](std::string room_id) {
                std::cout << "Selected room: " << room_id << '\n';
            })
    );

    m_LogoutEventDetachment = m_View->OnLogoutRequested.Attach(
        std::make_shared<core::event::util::Action<>>(
            [this] { this->HandleLogout(); }));
}

HomePresenter::~HomePresenter() {
    m_SelectRoomEventDetachment.Detach();
    m_LogoutEventDetachment.Detach();
}

void HomePresenter::HandleLogout() {
    const auto request_manager = m_Model->Logout();

    m_NavigationService->NavigateTo(
        Screen::Login,
        LoginScreenArgs{ std::move(request_manager), m_NavigationService });
}

} // namespace epsilon::features::home
