#pragma once

#include "../presenter/contracts/ILoginPresenter.hpp"
#include "../presenter/contracts/ILoginView.hpp"
#include <QObject>
#include <QString>
#include <memory>

class LoginView : public QObject, public ILoginView {
    Q_OBJECT

  public:
    explicit LoginView(QObject *parent = nullptr);
    void setPresenter(std::shared_ptr<ILoginPresenter> presenter);

    Q_INVOKABLE void AttemptLogin(const QString &email,
                                  const QString &password);

    void ShowLoginError(const std::string &error) override;
    void ShowLoginSuccess() override;

  public slots:
    void displayLogoutSuccess();

  signals:
    void loginFailed(const QString &errorMessage);
    void loginSucceeded();
    void showSuccessPopup();

  private:
    std::shared_ptr<ILoginPresenter> m_presenter;
};