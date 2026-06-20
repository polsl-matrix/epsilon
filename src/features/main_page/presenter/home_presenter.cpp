#include "home_presenter.hpp"
#include "src/features/main_page/presenter/contracts/ihome_view.hpp"
#include <memory>
#include <utility>

namespace epsilon::features::home {

HomePresenter::HomePresenter(std::weak_ptr<IHomeView> view)
    : m_View(std::move(view)) {
    if (auto view_lock = m_View.lock()) {
        view_lock->OnLogoutRequested = [this]() { HandleLogout(); };
    }
}

void HomePresenter::HandleLogout() {
    if (auto view = m_View.lock()) {
        view->ShowLogoutSuccess();
    }
}

}
