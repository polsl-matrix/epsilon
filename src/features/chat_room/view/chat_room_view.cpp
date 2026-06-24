#include "chat_room_view.hpp"

#include "../../../services/router/page_router.hpp"

#include <memory>
#include <string>
#include <utility>

#include <QString>

namespace epsilon::features::chat_room {

ChatRoomView::ChatRoomView(std::shared_ptr<services::router::PageRouter> page_router, QObject* parent)
    : QObject(parent), m_PageRouter(std::move(page_router)) {
    m_PageRouter->Bind("chatViewBackend", this);
}

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

void ChatRoomView::RequestEarlierMessages() {
    OnLoadEarlierRequested.Invoke();
}

void ChatRoomView::SetRoomName(const std::string& name) {
    setRoomName(QString::fromStdString(name));
}

void ChatRoomView::SetRoomAvatar(const std::string& avatar) {
    setRoomAvatar(QString::fromStdString(avatar));
}

void ChatRoomView::setRoomName(const QString& name) {
    if(name == m_RoomName) {
        return;
    }
    
    m_RoomName = name;

    emit roomNameChanged();
}

void ChatRoomView::setRoomAvatar(const QString& avatar) {
    if(avatar == m_RoomAvatar) {
        return;
    }
    
    m_RoomAvatar = avatar;

    emit roomAvatarChanged();
}

void ChatRoomView::AppendMessage(MessageDao message) {
    emit messageAppended(QString::fromStdString(message.Author), QString::fromStdString(message.Content), message.IsMe);
}

void ChatRoomView::PrependMessage(MessageDao message) {
    emit messagePrepended(QString::fromStdString(message.Author), QString::fromStdString(message.Content), message.IsMe);
}

}