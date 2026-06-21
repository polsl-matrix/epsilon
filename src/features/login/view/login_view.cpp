#include "login_view.hpp"

#include <qobject.h>
#include <qtmetamacros.h>
#include <string>

namespace epsilon::features::login {

LoginView::LoginView(QObject *parent) : QObject(parent) {}

void LoginView::AttemptLogin(const QString &username, const QString &password) {
    OnLoginRequested.Invoke(username.toStdString(), password.toStdString());
}

void LoginView::ShowLoginError(const std::string &error) {
    emit loginFailed(QString::fromStdString(error));
}

void LoginView::ShowLoginSuccess() { emit loginSucceeded(); }

void LoginView::DisplayLogoutSuccess() { emit showSuccessPopup(); }

}
