#include "chat_room_view.hpp"

namespace epsilon::features::chat_room::view {

ChatRoomView::ChatRoomView(const QString& roomName, const QString& roomAvatar, QObject* parent)
    : QObject(parent), m_RoomName(roomName), m_RoomAvatar(roomAvatar) {}

QString ChatRoomView::roomName() const {
    return m_RoomName;
}

QString ChatRoomView::roomAvatar() const {
    return m_RoomAvatar;
}

void ChatRoomView::SendMessage(const QString& text) {
    OnMessageSent.Invoke(text.toStdString());
}

void ChatRoomView::NotifyViewReady() {
    OnViewReady.Invoke();
}

void ChatRoomView::AppendMessage(const std::string& text, bool isMe) {
    emit messageAppended(QString::fromStdString(text), isMe);
}

}