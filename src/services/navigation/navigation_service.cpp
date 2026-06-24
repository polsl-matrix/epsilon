#include "navigation_service.hpp"

#include "args/home_screen_args.hpp"
#include "args/login_screen_args.hpp"
#include "args/registration_screen_args.hpp"
#include "inavigation_service.hpp"
#include "screen.hpp"

#include "../router/page_router.hpp"

#include "../../features/base/ipresenter.hpp"

#include "../../features/main_page/model/home_model.hpp"
#include "../../features/main_page/presenter/home_presenter.hpp"
#include "../../features/main_page/view/home_view.hpp"

#include "../../features/login/model/login_model.hpp"
#include "../../features/login/presenter/login_presenter.hpp"
#include "../../features/login/view/login_view.hpp"

#include "../../features/registration/model/registration_model.hpp"
#include "../../features/registration/presenter/registration_presenter.hpp"
#include "../../features/registration/view/registration_view.hpp"

#include <any>
#include <memory>

using namespace epsilon::features;

namespace epsilon::services::navigation {

NavigationService::NavigationService(
    std::shared_ptr<router::PageRouter> page_router)
    : m_PageRouter(page_router) {}

void NavigationService::NavigateTo(Screen screen, std::any args) {
    std::unique_ptr<base::IPresenter> new_presenter;

    switch (screen) {
    case Screen::Home: {
        auto home_args = std::any_cast<args::HomeScreenArgs>(args);
        auto view = std::make_unique<home::HomeView>(m_PageRouter);
        auto model = std::make_unique<home::HomeModel>(
            std::move(home_args.AuthenticatedRequestManager));
        new_presenter = std::make_unique<home::HomePresenter>(
            std::move(view), std::move(model),
            std::move(home_args.NavigationService));
        break;
    }
    case Screen::Login: {
        auto login_args = std::any_cast<args::LoginScreenArgs>(args);
        auto view = std::make_unique<login::LoginView>(m_PageRouter);
        auto model =
            std::make_unique<login::LoginModel>(login_args.RequestManager);
        new_presenter = std::make_unique<login::LoginPresenter>(
            std::move(view), std::move(model),
            std::move(login_args.NavigationService));
        break;
    }
    case Screen::Registration: {
        auto reg_args = std::any_cast<args::RegistrationScreenArgs>(args);
        auto view =
            std::make_unique<registration::RegistrationView>(m_PageRouter);
        auto model = std::make_unique<registration::RegistrationModel>(
            reg_args.request_manager);
        new_presenter = std::make_unique<registration::RegistrationPresenter>(
            std::move(view), std::move(model), reg_args.navigation_service);
        break;
    }
    }

    m_CurrentPresenter = std::move(new_presenter);
}
} // namespace epsilon::services::navigation
