#include "home_presenter.hpp"

#include "../../../core/event/util/action.hpp"
#include "../../../services/navigation/args/login_screen_args.hpp"
#include "../../../services/navigation/inavigation_service.hpp"
#include "../../../services/navigation/screen.hpp"
#include "src/features/main_page/presenter/contracts/ihome_view.hpp"

#include <iostream>
#include <memory>
#include <utility>

using epsilon::services::navigation::Screen;
using epsilon::services::navigation::args::LoginScreenArgs;

namespace epsilon::features::home {

HomePresenter::HomePresenter(
    std::unique_ptr<IHomeView> view,
    std::shared_ptr<INavigationService> navigation_service)
    : m_NavigationService(std::move(navigation_service)),
      m_View(std::move(view)) {
    m_LogoutEventDetachment = m_View->OnLogoutRequested.Attach(std::make_shared<core::event::util::Action<>>([this] {
        this->HandleLogout();
    }));
}

HomePresenter::~HomePresenter() {
    m_LogoutEventDetachment.Detach();
}

void HomePresenter::HandleLogout() {
    std::cout << "trying to log out :)\n";
    // m_NavigationService->NavigateTo(Screen::Login, LoginScreenArgs {});
}

} // namespace epsilon::features::home
