#include "login_view.hpp"

#include "../../../services/router/page_router.hpp"
#include "../../main_page/presenter/contracts/ihome_view.hpp"
#include "../../main_page/view/home_view.hpp"

#include <memory>
#include <utility>

#include <qobject.h>
#include <qtmetamacros.h>
#include <string>

namespace epsilon::features::login {

LoginView::LoginView(std::shared_ptr<LoginView::PageRouter> page_router,
                     QObject *parent)
    : QObject(parent), m_PageRouter(std::move(page_router)) {
    m_PageRouter->Display(m_QmlFilePath, m_QmlIdentifier, this);
}

void LoginView::AttemptLogin(const QString &username, const QString &password) {
    OnLoginRequested.Invoke(username.toStdString(), password.toStdString());
}

void LoginView::RequestRegistration() { OnRegistrationClicked.Invoke(); }

void LoginView::ShowLoginError(const std::string &error) {
    emit loginFailed(QString::fromStdString(error));
}

void LoginView::DisplayLogoutSuccess() { emit showSuccessPopup(); }

} // namespace epsilon::features::login