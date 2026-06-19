#include "HomeView.hpp"

HomeView::HomeView(QObject *parent) : QObject(parent) {}

void HomeView::AttemptLogout() {
    if (OnLogoutRequested) {
        OnLogoutRequested();
    }
}

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }