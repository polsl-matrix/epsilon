#pragma once

#include "../presenter/contracts/ihome_view.hpp"
#include "../../../services/router/page_router.hpp"

#include <memory>

#include <QObject>
#include <QString>

namespace epsilon::features::home {

class HomeView : public QObject, public IHomeView {
    Q_OBJECT

    using PageRouter = services::router::PageRouter;

    std::shared_ptr<PageRouter> m_PageRouter;

    QString m_QmlFilePath = "features/main_page/view/Home.qml";
    QString m_QmlIdentifier = "homeViewBackend";

  public:
    explicit HomeView(std::shared_ptr<PageRouter> page_router, QObject *parent = nullptr);

    Q_INVOKABLE void AttemptLogout();

    void ShowLogoutSuccess() override;

    Q_INVOKABLE void SelectRoom(const QString& room_id);

  signals:
    void logoutSucceeded();
};

}
