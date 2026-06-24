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

    using PageRouter = services::router::PageRouter;

    std::shared_ptr<PageRouter> m_PageRouter;

    QString m_QmlFilePath = "features/main_page/view/Home.qml";
    QString m_QmlIdentifier = "homeViewBackend";

    QVariantList m_Rooms;

  public:
    explicit HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent = nullptr);

    Q_INVOKABLE void AttemptLogout();

    void ShowLogoutSuccess() override;
    void SetRoomsList(const std::vector<RoomDto>& rooms) override;

    std::unique_ptr<chat_room::IChatRoomView> LoadChatRoomView() override;

    Q_INVOKABLE void SelectRoom(const QString& room_id);

    QVariantList rooms() const;

  signals:
    void logoutSucceeded();
    void chatRoomLoaded();
    void roomsChanged();
};

}
