#pragma once

#include "../contracts/ichat_room_view.hpp"
#include <QObject>
#include <QString>

namespace epsilon::features::chat_room::view {

class ChatRoomView : public QObject, public IChatRoomView {
    Q_OBJECT
    Q_PROPERTY(QString roomName READ roomName CONSTANT)
    Q_PROPERTY(QString roomAvatar READ roomAvatar CONSTANT)

public:
    ChatRoomView(const QString& roomName, const QString& roomAvatar, QObject* parent = nullptr);
    QString roomName() const;
    QString roomAvatar() const;
    Q_INVOKABLE void SendMessage(const QString& text);
    Q_INVOKABLE void NotifyViewReady();
    void AppendMessage(const std::string& text, bool isMe) override;

    signals:
        void messageAppended(const QString& text, bool isMe);

private:
    QString m_RoomName;
    QString m_RoomAvatar;
};

}