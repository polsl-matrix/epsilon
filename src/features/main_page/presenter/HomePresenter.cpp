#include "HomePresenter.hpp"

HomePresenter::HomePresenter(std::weak_ptr<IHomeView> view)
    : m_view(std::move(view)) {
    if (auto v = m_view.lock()) {
        v->OnLogoutRequested = [this]() { HandleLogout(); };
    }
}

void HomePresenter::HandleLogout() {
    if (auto view = m_view.lock()) {
        view->ShowLogoutSuccess();
    }
}