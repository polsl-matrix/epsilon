#include "login_view.hpp"

#include <qobject.h>
#include <qtmetamacros.h>
#include <string>

LoginView::LoginView(QObject *parent) : QObject(parent) {}

void LoginView::AttemptLogin(const QString &email, const QString &password) {
    OnLoginRequested.Invoke(email.toStdString(), password.toStdString());
}

void LoginView::ShowLoginError(const std::string &error) {
    emit loginFailed(QString::fromStdString(error));
}

void LoginView::ShowLoginSuccess() { emit loginSucceeded(); }

void LoginView::displayLogoutSuccess() { emit showSuccessPopup(); }