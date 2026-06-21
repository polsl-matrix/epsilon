#pragma once

#include "../presenter/contracts/ilogin_view.hpp"

#include <QObject>
#include <QString>

#include <string>

namespace epsilon::features::login {

class LoginView : public QObject, public ILoginView {
    Q_OBJECT

  public:
    explicit LoginView(QObject *parent = nullptr);

    Q_INVOKABLE void AttemptLogin(const QString &username,
                                  const QString &password);

    void ShowLoginError(const std::string &error) override;
    void ShowLoginSuccess() override;

  
    void DisplayLogoutSuccess();

  signals:
    void loginFailed(const QString &_t1);
    void loginSucceeded();
    void showSuccessPopup();
};

}
