#pragma once

#include "contracts/ihome_presenter.hpp"
#include "contracts/ihome_view.hpp"
#include <memory>

class HomePresenter : public IHomePresenter {
  public:
    explicit HomePresenter(std::weak_ptr<IHomeView> view);
    void HandleLogout() override;

  private:
    std::weak_ptr<IHomeView> m_View;
};