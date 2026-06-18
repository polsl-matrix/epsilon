#include "HomePresenter.hpp"

HomePresenter::HomePresenter(IHomeView* view)
    : m_view(view) {}

void HomePresenter::HandleLogout() {
    m_view->ShowLogoutSuccess();
}