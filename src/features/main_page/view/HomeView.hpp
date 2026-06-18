#pragma once

#include <QObject>
#include "../presenter/contracts/IHomeView.hpp"
#include "../presenter/contracts/IHomePresenter.hpp"

class HomeView : public QObject, public IHomeView {
    Q_OBJECT

public:
    explicit HomeView(QObject* parent = nullptr);
    void setPresenter(IHomePresenter* presenter);

    Q_INVOKABLE void AttemptLogout();

    void ShowLogoutSuccess() override;

    signals:
        void logoutSucceeded();

private:
    IHomePresenter* m_presenter;
};