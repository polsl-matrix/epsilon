#pragma once

#include "../../base/ipresenter.hpp"
#include "contracts/ihome_view.hpp"

#include <memory>

namespace epsilon::features::home {

class HomePresenter : public base::IPresenter {
  public:
    explicit HomePresenter(std::unique_ptr<IHomeView> view);
    void HandleLogout();

  private:
    std::unique_ptr<IHomeView> m_View;
};

}
