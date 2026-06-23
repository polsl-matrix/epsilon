#include "login_presenter.hpp"
#include "../../../core/event/util/action.hpp"
#include "../../../services/matrix/requests/authenticated_request_manager.hpp"
#include "../../../services/navigation/args/home_screen_args.hpp"
#include "../../../services/navigation/args/registration_screen_args.hpp"
#include "../../../services/navigation/inavigation_service.hpp"
#include "../../../services/navigation/screen.hpp"
#include "../model/login_model.hpp"
#include "contracts/ilogin_view.hpp"

#include <QTimer>
#include <memory>
#include <string>
#include <utility>

using AuthenticatedRequestManager = epsilon::services::matrix::requests::AuthenticatedRequestManager;

namespace epsilon::features::login {

LoginPresenter::LoginPresenter(
    std::unique_ptr<ILoginView> view, std::unique_ptr<LoginModel> model,
    std::shared_ptr<services::navigation::INavigationService> navigation_service)
    : m_View(std::move(view)), m_Model(std::move(model)),
      m_NavigationService(std::move(navigation_service)),
      m_LoginRequestDetachment([]() {}),
      m_RegistrationClickDetachment([]() {}) {

    m_LoginRequestDetachment = m_View->OnLoginRequested.Attach<
        epsilon::core::event::util::Action<std::string, std::string>>(
        [this](const std::string &username, const std::string &password) {
            HandleLogin(username, password);
        });

    m_RegistrationClickDetachment = m_View->OnRegistrationClicked.Attach<
        epsilon::core::event::util::Action<>>(
        [this]() {
            if (m_NavigationService && m_Model) {
                auto nav = m_NavigationService;
                auto req = m_Model->GetRequestManager();
                QTimer::singleShot(0, [nav, req]() {
                    if (nav && req) {
                        nav->NavigateTo(
                            services::navigation::Screen::Registration,
                            services::navigation::args::RegistrationScreenArgs{ req, nav }
                        );
                    }
                });
            }
        });
}

void LoginPresenter::HandleLogin(const std::string &username, const std::string &password) {
    if (username.empty()) {
        m_View->ShowLoginError("Username cannot be empty");
        return;
    }

    if (password.empty()) {
        m_View->ShowLoginError("Password cannot be empty");
        return;
    }

    if (m_Model) {
        std::weak_ptr<ILoginView> view_pointer = m_View;
        std::weak_ptr<LoginModel> model_pointer = m_Model;
        std::weak_ptr<services::navigation::INavigationService> navigation_service_pointer = m_NavigationService;

        m_Model->Authenticate(username, password)
            ->Then([view_pointer, model_pointer, navigation_service_pointer](auto login_data) {
                if (view_pointer.expired() || model_pointer.expired() || navigation_service_pointer.expired()) {
                    return;
                }

                auto view = view_pointer.lock();
                auto model = model_pointer.lock();
                auto navigation_service = navigation_service_pointer.lock();

                if (login_data.has_value()) {
                    navigation_service->NavigateTo(
                        services::navigation::Screen::Home,
                        services::navigation::args::HomeScreenArgs{
                            std::make_shared<AuthenticatedRequestManager>(
                                model->GetRequestManager(),
                                login_data.value().AccessToken),
                            navigation_service });
                } else {
                    const auto error = login_data.error();

                    switch (error) {
                    case LoginError::IncorrectAuthenticationData:
                        view->ShowLoginError("Incorrect username or password");
                        break;

                    case LoginError::UserDeactivated:
                        view->ShowLoginError("This user has been deactivated");
                        break;

                    case LoginError::ReachedRequestLimit:
                        view->ShowLoginError("Slow down! Too many requests at once");
                        break;

                    case LoginError::RequestFailed:
                        view->ShowLoginError("HTTP request failed. Make sure you're connected to the Internet");
                        break;

                    default:
                        view->ShowLoginError("Unknown error has occured");
                    }
                }
            });
    }
}

}