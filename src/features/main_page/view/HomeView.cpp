#include "HomeView.hpp"

HomeView::HomeView(QObject* parent) : QObject(parent), m_presenter(nullptr) {}

void HomeView::setPresenter(IHomePresenter* presenter) {
    m_presenter = presenter;
}

void HomeView::AttemptLogout() {
    if (m_presenter) {
        m_presenter->HandleLogout();
    }
}

void HomeView::ShowLogoutSuccess() {
    emit logoutSucceeded();
}