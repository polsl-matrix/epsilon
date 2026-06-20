#include "LoginPresenter.hpp"
#include "../../../core/event/util/action.hpp"
#include "../model/LoginModel.hpp"
#include "contracts/ILoginView.hpp"

#include <memory>
#include <string>
#include <utility>

LoginPresenter::LoginPresenter(std::weak_ptr<ILoginView> view,
                               std::shared_ptr<LoginModel> model)
    : m_View(std::move(view)), m_Model(std::move(model)),
      m_LoginRequestDetachment([]() {}) {

    if (auto view_ptr = m_View.lock()) {
        m_LoginRequestDetachment = view_ptr->OnLoginRequested.template Attach<
            epsilon::core::event::util::Action<std::string, std::string>>(
            [this](const std::string& email, const std::string& password) {
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

    if (m_Model && m_Model->Authenticate(email, password)) {
        view->ShowLoginSuccess();
    } else {
        view->ShowLoginError("Incorrect email or password");
    }
}