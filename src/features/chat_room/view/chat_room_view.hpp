#pragma once

#include "../presenter/contracts/ichat_room_view.hpp"
#include "../presenter/contracts/message_dao.hpp"
#include "../../../services/router/page_router.hpp"

#include <memory>
#include <string>

#include <QObject>
#include <QString>

namespace epsilon::features::chat_room {

class ChatRoomView : public QObject, public IChatRoomView {
    Q_OBJECT
    Q_PROPERTY(QString roomName READ roomName WRITE setRoomName NOTIFY roomNameChanged)
    Q_PROPERTY(QString roomAvatar READ roomAvatar WRITE setRoomAvatar NOTIFY roomAvatarChanged)

    std::shared_ptr<services::router::PageRouter> m_PageRouter;

public:
    ChatRoomView(std::shared_ptr<services::router::PageRouter> page_router, QObject* parent = nullptr);
    
    QString roomName() const;
    QString roomAvatar() const;
    Q_INVOKABLE void SendMessage(const QString& text);
    Q_INVOKABLE void RequestEarlierMessages();

    void SetRoomName(const std::string& name) override;
    void SetRoomAvatar(const std::string& avatar) override;

    void setRoomName(const QString& name);
    void setRoomAvatar(const QString& avatar);

    void AppendMessage(MessageDao message) override;
    void PrependMessage(MessageDao message) override;

signals:
    void messageAppended(const QString& senderName, const QString& text, bool isMe);
    void messagePrepended(const QString& senderName, const QString& text, bool isMe);
    void roomNameChanged();
    void roomAvatarChanged();

private:
    QString m_RoomName;
    QString m_RoomAvatar;
};

}