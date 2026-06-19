#pragma once

#include "../presenter/contracts/IHomeView.hpp"
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