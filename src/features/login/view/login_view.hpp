#pragma once

#include "../../../services/router/page_router.hpp"
#include "../presenter/contracts/ilogin_view.hpp"

#include <QObject>
#include <QString>

#include <memory>
#include <string>

namespace epsilon::features::login {

class LoginView : public QObject, public ILoginView {
    Q_OBJECT

    using PageRouter = services::router::PageRouter;

    std::shared_ptr<PageRouter> m_PageRouter;

    QString m_QmlFilePath = "features/login/view/Login.qml";
    QString m_QmlIdentifier = "loginViewBackend";

  public:
    explicit LoginView(std::shared_ptr<PageRouter> page_router, QObject *parent = nullptr);

    Q_INVOKABLE void AttemptLogin(const QString &username,
                                  const QString &password);

    void ShowLoginError(const std::string &error) override;
  
    void DisplayLogoutSuccess();

  signals:
    void loginFailed(const QString &_t1);
    void showSuccessPopup();
};

}
