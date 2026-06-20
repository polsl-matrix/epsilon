#pragma once

#include "../presenter/contracts/ihome_view.hpp"
#include <QObject>

class HomeView : public QObject, public IHomeView {
    Q_OBJECT

  public:
    explicit HomeView(QObject *parent = nullptr);

    Q_INVOKABLE void AttemptLogout();

    void ShowLogoutSuccess() override;

  signals:
    void logoutSucceeded();
};