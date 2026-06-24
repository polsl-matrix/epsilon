#pragma once

#include "../../base/ipresenter.hpp"
#include "contracts/ihome_view.hpp"
#include "../model/home_model.hpp"
#include "../../../core/event/detachment.hpp"
#include "../../../services/navigation/inavigation_service.hpp"

#include <memory>

namespace epsilon::features::home {

class HomePresenter : public base::IPresenter {
    using INavigationService = services::navigation::INavigationService;

    std::shared_ptr<INavigationService> m_NavigationService;

    core::event::Detachment m_LogoutEventDetachment;

  public:
    explicit HomePresenter(std::unique_ptr<IHomeView> view, std::unique_ptr<HomeModel> model, std::shared_ptr<INavigationService> navigation_service);
    ~HomePresenter();
    void HandleLogout();

  private:
    std::unique_ptr<IHomeView> m_View;
    std::unique_ptr<HomeModel> m_Model;
};

}
