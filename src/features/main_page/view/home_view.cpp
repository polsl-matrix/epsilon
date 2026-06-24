#include "home_view.hpp"

#include "../../../services/router/page_router.hpp"
#include "../../chat_room/view/chat_room_view.hpp"
#include "../presenter/contracts/ihome_view.hpp"

#include <memory>
#include <iostream>

#include <QString>
#include <qobject.h>
#include <qtmetamacros.h>
#include <QVariantList>

namespace epsilon::features::home {

HomeView::HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent)
    : QObject(parent), m_PageRouter(page_router) {
    m_PageRouter->Display(m_QmlFilePath, m_QmlIdentifier, this);
}

void HomeView::AttemptLogout() { OnLogoutRequested.Invoke(); }

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }

void HomeView::SetRoomsList(const std::vector<RoomDto>& rooms) {
    m_Rooms.clear();
    std::cout << "Reloading rooms...\n";
    for (const auto& room : rooms) {
        QVariantMap roomMap;
        roomMap["room_id"] = QString::fromStdString(room.Id);
        roomMap["name"] = QString::fromStdString(room.Name);
        
        std::cout << '\t' << room.Id << '\n';

        QString avatarInit = room.Name.empty() ? "?" : QString(room.Name[0]).toUpper();
        roomMap["avatar"] = avatarInit;
        roomMap["notif"] = 0;

        m_Rooms.append(roomMap);
    }
    emit roomsChanged();
}

QVariantList HomeView::rooms() const {
    return m_Rooms;
}

std::unique_ptr<chat_room::IChatRoomView> HomeView::LoadChatRoomView() {
    emit chatRoomLoaded();
    return std::make_unique<chat_room::ChatRoomView>(m_PageRouter);
}

void HomeView::SelectRoom(const QString &room_id) {
    OnChatSelected.Invoke(room_id.toStdString());
}

} // namespace epsilon::features::home
