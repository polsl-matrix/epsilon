#pragma once

#include "../presenter/contracts/ILoginView.hpp"

#include <QObject>
#include <QString>

#include <string>

class LoginView : public QObject, public ILoginView {
    Q_OBJECT

  public:
    explicit LoginView(QObject *parent = nullptr);

    Q_INVOKABLE void AttemptLogin(const QString &email,
                                  const QString &password);

    void ShowLoginError(const std::string &error) override;
    void ShowLoginSuccess() override;

  public slots:
    void displayLogoutSuccess();

  signals:
    void loginFailed(const QString &error_message);
    void loginSucceeded();
    void showSuccessPopup();
};