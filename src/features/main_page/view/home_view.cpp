#include "home_view.hpp"

#include "../../../services/router/page_router.hpp"

#include <memory>

#include <qobject.h>
#include <qtmetamacros.h>
#include <QString>

namespace epsilon::features::home {

HomeView::HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent)
    : QObject(parent), m_PageRouter(page_router) {
    m_PageRouter->Display(m_QmlFilePath, m_QmlIdentifier, this);
}

void HomeView::AttemptLogout() { OnLogoutRequested.Invoke(); }

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }

void HomeView::SelectRoom(const QString& room_id) {
    OnChatSelected.Invoke(room_id.toStdString());
}

} // namespace epsilon::features::home
