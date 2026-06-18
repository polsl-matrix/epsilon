#include "LoginPresenter.hpp"

LoginPresenter::LoginPresenter(ILoginView* view, LoginModel* model)
    : m_view(view), m_model(model) {}

void LoginPresenter::HandleLogin(const std::string& email, const std::string& password) {
    if (email.empty() || password.empty()) {
        m_view->ShowLoginError("Pola nie mogą być puste.");
        return;
    }

    if (m_model->Authenticate(email, password)) {
        m_view->ShowLoginSuccess();
    } else {
        m_view->ShowLoginError("Nieprawidłowy email lub hasło.");
    }
}