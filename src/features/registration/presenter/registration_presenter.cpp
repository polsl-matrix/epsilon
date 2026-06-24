#include "registration_presenter.hpp"
#include "../../../core/event/util/action.hpp"
#include "../../../services/matrix/requests/authenticated_request_manager.hpp"
#include "../../../services/navigation/args/home_screen_args.hpp"
#include "../../../services/navigation/args/login_screen_args.hpp"
#include "../../../services/navigation/inavigation_service.hpp"
#include "../../../services/navigation/screen.hpp"
#include "../model/registration_model.hpp"
#include "contracts/iregistration_view.hpp"

#include <algorithm>
#include <cctype>
#include <memory>
#include <string>
#include <utility>

using AuthenticatedRequestManager = epsilon::services::matrix::requests::AuthenticatedRequestManager;

namespace epsilon::features::registration {

RegistrationPresenter::RegistrationPresenter(
    std::unique_ptr<IRegistrationView> view,
    std::unique_ptr<RegistrationModel> model,
    std::shared_ptr<services::navigation::INavigationService> navigation_service)
    : m_View(std::move(view)),
      m_Model(std::move(model)),
      m_NavigationService(std::move(navigation_service)) {

    m_RegistrationRequestDetachment = m_View->OnRegistrationRequested.Attach<
        epsilon::core::event::util::Action<std::string, std::string, std::string>>(
        [this](const std::string &username, const std::string &password, const std::string &repeat_password) {
            HandleRegistration(username, password, repeat_password);
        });

    m_LoginLinkDetachment = m_View->OnLoginLinkClicked.Attach<
        epsilon::core::event::util::Action<>>(
        [this]() {
            if (m_NavigationService && m_Model) {
                auto nav = m_NavigationService;
                auto req = m_Model->GetRequestManager();

                nav->NavigateTo(
                    services::navigation::Screen::Login,
                    services::navigation::args::LoginScreenArgs{ req, nav }
                );
            }
        });
}

void RegistrationPresenter::HandleRegistration(const std::string &username, const std::string &password, const std::string &repeat_password) {
    if (username.empty()) {
        m_View->ShowRegistrationError("Username cannot be empty");
        return;
    }

    if (password.empty()) {
        m_View->ShowRegistrationError("Password cannot be empty");
        return;
    }

    if (password != repeat_password) {
        m_View->ShowRegistrationError("Passwords do not match");
        return;
    }

    if (password.length() < 8) {
        m_View->ShowRegistrationError("Password must be at least 8 characters long");
        return;
    }

    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;

    for (char c : password) {
        if (std::isupper(c)) has_upper = true;
        if (std::islower(c)) has_lower = true;
        if (std::isdigit(c)) has_digit = true;
    }

    if (!has_upper || !has_lower || !has_digit) {
        m_View->ShowRegistrationError("Password needs at least: 1 uppercase, 1 lowercase, and 1 number");
        return;
    }

    if (m_Model) {
        std::weak_ptr<IRegistrationView> view_ptr = m_View;
        std::weak_ptr<RegistrationModel> model_ptr = m_Model;
        std::weak_ptr<services::navigation::INavigationService> nav_ptr = m_NavigationService;

        m_Model->Register(username, password)->Then([view_ptr, model_ptr, nav_ptr](auto reg_data) {
            if (view_ptr.expired() || model_ptr.expired() || nav_ptr.expired()) {
                return;
            }

            auto view = view_ptr.lock();
            auto model = model_ptr.lock();
            auto nav = nav_ptr.lock();

            if (reg_data.has_value()) {
                const auto access_token = reg_data.value().AccessToken;

                nav->NavigateTo(
                    services::navigation::Screen::Home,
                    services::navigation::args::HomeScreenArgs{
                        std::make_shared<AuthenticatedRequestManager>(
                            model->GetRequestManager(),
                            access_token),
                        nav
                    }
                );
            } else {
                const auto error = reg_data.error();

                switch (error) {
                case RegistrationError::UsernameTaken:
                    view->ShowRegistrationError("Provided username is already taken");
                    break;

                case RegistrationError::ReachedRequestLimit:
                    view->ShowRegistrationError("Slow down! Too many requests at once");
                    break;

                case RegistrationError::RequestFailed:
                    view->ShowRegistrationError("HTTP request failed. Make sure you're connected to the Internet");
                    break;

                default:
                    view->ShowRegistrationError("An unknown error has occurred");
                }
            }
        });
    }
}

}