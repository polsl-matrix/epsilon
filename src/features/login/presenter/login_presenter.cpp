#include "login_presenter.hpp"
#include "../../../core/event/util/action.hpp"
#include "../model/login_model.hpp"
#include "contracts/ilogin_view.hpp"

#include <memory>
#include <string>
#include <utility>
#include <iostream>

namespace epsilon::features::login {

LoginPresenter::LoginPresenter(std::weak_ptr<ILoginView> view,
                               std::shared_ptr<LoginModel> model)
    : m_View(std::move(view)), m_Model(std::move(model)),
      m_LoginRequestDetachment([]() {}) {

    if (auto view_ptr = m_View.lock()) {
        m_LoginRequestDetachment = view_ptr->OnLoginRequested.template Attach<
            epsilon::core::event::util::Action<std::string, std::string>>(
            [this](const std::string &email, const std::string &password) {
                HandleLogin(email, password);
            });
    }
}

void LoginPresenter::HandleLogin(const std::string &email,
                                 const std::string &password) {
    auto view = m_View.lock();
    if (!view) {
        return;
    }

    if (email.empty()) {
        view->ShowLoginError("Email cannot be empty");
        return;
    }

    if (password.empty()) {
        view->ShowLoginError("Password cannot be empty");
        return;
    }

    if (m_Model) {
        m_Model->Authenticate(email, password)->Then([view](auto login_data) {
            if(login_data.has_value()) {
                view->ShowLoginSuccess();
            } else {
                const auto error = login_data.error();
    
                switch (error)
                {
                case LoginError::IncorrectAuthenticationData:
                    view->ShowLoginError("Incorrect email or password");
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

        std::cout << "set up the future\n";
    }
}

}
