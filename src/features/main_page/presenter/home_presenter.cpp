#include "home_presenter.hpp"

#include "../../../services/navigation/args/login_screen_args.hpp"
#include "../../../services/navigation/inavigation_service.hpp"
#include "../../../services/navigation/screen.hpp"
#include "src/features/main_page/presenter/contracts/ihome_view.hpp"

#include <memory>
#include <utility>

using epsilon::services::navigation::Screen;
using epsilon::services::navigation::args::LoginScreenArgs;

namespace epsilon::features::home {

HomePresenter::HomePresenter(
    std::unique_ptr<IHomeView> view,
    std::shared_ptr<INavigationService> navigation_service)
    : m_View(std::move(view)), m_NavigationService(navigation_service) {
    m_View->OnLogoutRequested = [this]() { HandleLogout(); };
}

void HomePresenter::HandleLogout() {
    // m_NavigationService->NavigateTo(Screen::Login, LoginScreenArgs {});
}

} // namespace epsilon::features::home
