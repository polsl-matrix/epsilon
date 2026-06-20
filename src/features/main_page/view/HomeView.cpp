#include "HomeView.hpp"
#include <qobject.h>
#include <qtmetamacros.h>

HomeView::HomeView(QObject *parent) : QObject(parent) {}

void HomeView::AttemptLogout() {
    if (OnLogoutRequested) {
        OnLogoutRequested();
    }
}

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }