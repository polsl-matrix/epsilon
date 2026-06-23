#pragma once

#include "../../base/ipresenter.hpp"
#include "contracts/ihome_view.hpp"
#include "../../../services/navigation/inavigation_service.hpp"

#include <memory>

namespace epsilon::features::home {

class HomePresenter : public base::IPresenter {
    using INavigationService = services::navigation::INavigationService;

    std::shared_ptr<INavigationService> m_NavigationService;

  public:
    explicit HomePresenter(std::unique_ptr<IHomeView> view, std::shared_ptr<INavigationService> navigation_service);
    void HandleLogout();

  private:
    std::unique_ptr<IHomeView> m_View;
};

}
