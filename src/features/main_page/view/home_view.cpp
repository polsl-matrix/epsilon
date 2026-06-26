#include "home_view.hpp"

#include "../../../services/router/page_router.hpp"
#include "../../chat_room/view/chat_room_view.hpp"
#include "../presenter/contracts/ihome_view.hpp"

#include <memory>

#include <QString>
#include <QVariantList>
#include <qobject.h>
#include <qtmetamacros.h>

namespace epsilon::features::home {

HomeView::HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent)
    : QObject(parent), m_PageRouter(page_router) {
    m_PageRouter->Display(m_QmlFilePath, m_QmlIdentifier, this);
}

void HomeView::AttemptLogout() { OnLogoutRequested.Invoke(); }

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }

void HomeView::SetRoomsList(const std::vector<RoomDto> &rooms) {
    m_Rooms.clear();

    for (const auto &room : rooms) {
        QVariantMap roomMap;
        roomMap["room_id"] = QString::fromStdString(room.Id);
        roomMap["name"] = QString::fromStdString(room.Name);

        QString avatarInit =
            room.Name.empty() ? "?" : QString(room.Name[0]).toUpper();
        roomMap["avatar"] = avatarInit;
        roomMap["notif"] = 0;

        m_Rooms.append(roomMap);
    }
    emit roomsChanged();
}

QString HomeView::username() const {
    return m_Username;
}

void HomeView::setUsername(const QString& newUsername) {
    if (m_Username != newUsername) {
        m_Username = newUsername;
        emit usernameChanged();
    }
}

void HomeView::SetUserName(std::string user_name) {
    setUsername(QString::fromStdString(user_name));
}

QVariantList HomeView::rooms() const { return m_Rooms; }

std::unique_ptr<chat_room::IChatRoomView> HomeView::LoadChatRoomView() {
    emit chatRoomLoaded();
    return std::make_unique<chat_room::ChatRoomView>(m_PageRouter);
}

void HomeView::SelectRoom(const QString &room_id) {
    OnChatSelected.Invoke(room_id.toStdString());
}

} // namespace epsilon::features::home
