#include "home_view.hpp"

#include "../../../services/router/page_router.hpp"
#include "../../chat_room/view/chat_room_view.hpp"
#include "../presenter/contracts/ihome_view.hpp"

#include <memory>

#include <QString>
#include <qobject.h>
#include <qtmetamacros.h>

namespace epsilon::features::home {

HomeView::HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent)
    : QObject(parent), m_PageRouter(page_router) {
    m_PageRouter->Display(m_QmlFilePath, m_QmlIdentifier, this);
}

void HomeView::AttemptLogout() { OnLogoutRequested.Invoke(); }

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }

std::unique_ptr<chat_room::IChatRoomView> HomeView::LoadChatRoomView() {
    emit chatRoomLoaded();
    return std::make_unique<chat_room::ChatRoomView>(m_PageRouter);
}

void HomeView::SelectRoom(const QString &room_id) {
    OnChatSelected.Invoke(room_id.toStdString());
}

} // namespace epsilon::features::home
