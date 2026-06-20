#include "home_view.hpp"
#include <qobject.h>
#include <qtmetamacros.h>

namespace epsilon::features::home {

HomeView::HomeView(QObject *parent) : QObject(parent) {}

void HomeView::AttemptLogout() {
    if (OnLogoutRequested) {
        OnLogoutRequested();
    }
}

void HomeView::ShowLogoutSuccess() { emit logoutSucceeded(); }

}
