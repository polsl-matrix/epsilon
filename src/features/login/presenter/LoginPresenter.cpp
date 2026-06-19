#include "LoginPresenter.hpp"
#include "../../../core/event/util/action.hpp"
#include "contracts/ILoginView.hpp"

#include <memory>
#include <string>

LoginPresenter::LoginPresenter(std::weak_ptr<ILoginView> view,
                               std::shared_ptr<LoginModel> model)
    : m_View(std::move(view)), m_Model(std::move(model)),
      // Inicjalizujemy detachment puste, nadpiszemy je zaraz jeśli widok jest
      // dostępny
      m_LoginRequestDetachment([]() {}) {

    if (auto v = m_View.lock()) {
        m_LoginRequestDetachment = v->OnLoginRequested.Attach<
            epsilon::core::event::util::Action<std::string, std::string>>(
            [this](std::string email, std::string password) {
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

    if (email.empty() || password.empty()) {
        view->ShowLoginError("Pola nie mogą być puste.");
        return;
    }

    if (m_Model && m_Model->Authenticate(email, password)) {
        view->ShowLoginSuccess();
    } else {
        view->ShowLoginError("Nieprawidłowy email lub hasło.");
    }
}