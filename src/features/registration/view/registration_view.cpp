#include "registration_view.hpp"
#include "../../../services/router/page_router.hpp"

#include <memory>
#include <string>
#include <utility>

namespace epsilon::features::registration {

RegistrationView::RegistrationView(std::shared_ptr<PageRouter> page_router,
                                   QObject *parent)
    : QObject(parent), m_PageRouter(std::move(page_router)) {
    m_PageRouter->Display(m_QmlFilePath, m_QmlIdentifier, this);
}

void RegistrationView::AttemptRegistration(const QString &username,
                                           const QString &password,
                                           const QString &repeatPassword) {
    OnRegistrationRequested.Invoke(username.toStdString(),
                                   password.toStdString(),
                                   repeatPassword.toStdString());
}

void RegistrationView::RequestNavigateToLogin() { OnLoginLinkClicked.Invoke(); }

void RegistrationView::ShowRegistrationError(const std::string &error) {
    emit registrationFailed(QString::fromStdString(error));
}

} // namespace epsilon::features::registration