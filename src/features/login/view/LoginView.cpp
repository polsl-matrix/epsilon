#include "LoginView.hpp"

LoginView::LoginView(QObject *parent) : QObject(parent) {}

void LoginView::setPresenter(std::shared_ptr<ILoginPresenter> presenter) {
    m_presenter = std::move(presenter);
}

void LoginView::AttemptLogin(const QString &email, const QString &password) {
    if (m_presenter) {
        m_presenter->HandleLogin(email.toStdString(), password.toStdString());
    }
}

void LoginView::ShowLoginError(const std::string &error) {
    emit loginFailed(QString::fromStdString(error));
}

void LoginView::ShowLoginSuccess() { emit loginSucceeded(); }

void LoginView::displayLogoutSuccess() { emit showSuccessPopup(); }