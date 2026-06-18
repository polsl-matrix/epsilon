#include "LoginView.hpp"

LoginView::LoginView(QObject* parent) : QObject(parent), m_presenter(nullptr) {}

void LoginView::setPresenter(ILoginPresenter* presenter) {
    m_presenter = presenter;
}

void LoginView::AttemptLogin(const QString& email, const QString& password) {
    if (m_presenter) {
        m_presenter->HandleLogin(email.toStdString(), password.toStdString());
    }
}

void LoginView::ShowLoginError(const std::string& error) {
    emit loginFailed(QString::fromStdString(error));
}

void LoginView::ShowLoginSuccess() {
    emit loginSucceeded();
}

void LoginView::displayLogoutSuccess() {
    emit showSuccessPopup();
}