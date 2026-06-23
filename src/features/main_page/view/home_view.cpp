#include "home_view.hpp"

#include "../../../services/router/page_router.hpp"

#include <memory>

#include <qobject.h>
#include <qtmetamacros.h>

namespace epsilon::features::home {

HomeView::HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent)
    : QObject(parent), m_PageRouter(page_router) {
    m_PageRouter->Display(m_QmlFilePath, m_QmlIdentifier, this);
}

void HomeView::AttemptLogout() { OnLogoutRequested.Invoke(); }

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }

} // namespace epsilon::features::home
