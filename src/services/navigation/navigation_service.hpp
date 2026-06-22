#pragma once

#include "inavigation_service.hpp"
#include "screen.hpp"
#include "../../features/base/ipresenter.hpp"
#include "../router/page_router.hpp"

#include <any>
#include <memory>

namespace epsilon::services::navigation {

class NavigationService : public INavigationService {
    std::unique_ptr<features::base::IPresenter> m_CurrentPresenter;
    std::shared_ptr<router::PageRouter> m_PageRouter;

  public:
    NavigationService(std::shared_ptr<router::PageRouter> page_router);

    virtual void NavigateTo(Screen screen, std::any args = {});
};

}
