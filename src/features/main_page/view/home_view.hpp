#pragma once

#include "../presenter/contracts/ihome_view.hpp"
#include "../../../services/router/page_router.hpp"

#include <memory>

#include <QObject>
#include <QString>
#include <QVariantList>

namespace epsilon::features::home {

class HomeView : public QObject, public IHomeView {
    Q_OBJECT
    Q_PROPERTY(QVariantList rooms READ rooms NOTIFY roomsChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)

    using PageRouter = services::router::PageRouter;

    std::shared_ptr<PageRouter> m_PageRouter;

    QString m_QmlFilePath = "features/main_page/view/Home.qml";
    QString m_QmlIdentifier = "homeViewBackend";

    QVariantList m_Rooms;
    QString m_Username = "Anonymous";

  public:
    explicit HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent = nullptr);

    Q_INVOKABLE void AttemptLogout();

    void ShowLogoutSuccess() override;
    void SetRoomsList(const std::vector<RoomDto>& rooms) override;

    std::unique_ptr<chat_room::IChatRoomView> LoadChatRoomView() override;
    void SetUserName(std::string user_name) override;

    Q_INVOKABLE void SelectRoom(const QString& room_id);
    QString username() const;
    Q_INVOKABLE void setUsername(const QString& newUsername);

    QVariantList rooms() const;

  signals:
    void logoutSucceeded();
    void chatRoomLoaded();
    void roomsChanged();
    void usernameChanged();
};

}
