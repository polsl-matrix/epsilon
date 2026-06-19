#include "LoginPresenter.hpp"

LoginPresenter::LoginPresenter(std::weak_ptr<ILoginView> view,
                               std::shared_ptr<LoginModel> model)
    : m_view(std::move(view)), m_model(std::move(model)) {}

void LoginPresenter::HandleLogin(const std::string &email,
                                 const std::string &password) {
    auto view = m_view.lock();
    if (!view) {
        return;
    }

    if (email.empty() || password.empty()) {
        view->ShowLoginError("Pola nie mogą być puste.");
        return;
    }

    if (m_model && m_model->Authenticate(email, password)) {
        view->ShowLoginSuccess();
    } else {
        view->ShowLoginError("Nieprawidłowy email lub hasło.");
    }
}