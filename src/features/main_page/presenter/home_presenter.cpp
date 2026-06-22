#include "home_presenter.hpp"
#include "src/features/main_page/presenter/contracts/ihome_view.hpp"
#include <memory>
#include <utility>

namespace epsilon::features::home {

HomePresenter::HomePresenter(std::unique_ptr<IHomeView> view) : m_View(std::move(view)) {
    m_View->OnLogoutRequested = [this]() { HandleLogout(); };
}

void HomePresenter::HandleLogout() {
    m_View->ShowLogoutSuccess();
}

}
