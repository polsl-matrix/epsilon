#pragma once

#include <QObject>
#include <QString>
#include "../presenter/contracts/ILoginView.hpp"
#include "../presenter/contracts/ILoginPresenter.hpp"

class LoginView : public QObject, public ILoginView {
    Q_OBJECT

public:
    explicit LoginView(QObject* parent = nullptr);
    void setPresenter(ILoginPresenter* presenter);

    Q_INVOKABLE void AttemptLogin(const QString& email, const QString& password);

    void ShowLoginError(const std::string& error) override;
    void ShowLoginSuccess() override;

public slots:
    void displayLogoutSuccess();

    signals:
        void loginFailed(const QString& errorMessage);
    void loginSucceeded();
    void showSuccessPopup();

private:
    ILoginPresenter* m_presenter;
};