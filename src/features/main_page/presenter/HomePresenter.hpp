#pragma once

#include "contracts/IHomePresenter.hpp"
#include "contracts/IHomeView.hpp"
#include <memory>

class HomePresenter : public IHomePresenter {
  public:
    explicit HomePresenter(std::weak_ptr<IHomeView> view);
    void HandleLogout() override;

  private:
    std::weak_ptr<IHomeView> m_view;
};