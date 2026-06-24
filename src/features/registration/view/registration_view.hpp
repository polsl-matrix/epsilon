#pragma once

#include "../../../services/router/page_router.hpp"
#include "../presenter/contracts/iregistration_view.hpp"

#include <QObject>
#include <QString>
#include <memory>
#include <string>

namespace epsilon::features::registration {

class RegistrationView : public QObject, public IRegistrationView {
    Q_OBJECT

    using PageRouter = services::router::PageRouter;

    std::shared_ptr<PageRouter> m_PageRouter;

    QString m_QmlFilePath = "features/registration/view/Registration.qml";
    QString m_QmlIdentifier = "registrationViewBackend";

public:
    explicit RegistrationView(std::shared_ptr<PageRouter> page_router, QObject *parent = nullptr);

    Q_INVOKABLE void AttemptRegistration(const QString &username, const QString &password, const QString &repeatPassword);
    Q_INVOKABLE void RequestNavigateToLogin();

    void ShowRegistrationError(const std::string &error) override;

    signals:
        void registrationFailed(const QString &_t1);
};

}