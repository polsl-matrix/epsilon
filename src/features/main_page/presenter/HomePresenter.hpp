#pragma once

#include "contracts/IHomePresenter.hpp"
#include "contracts/IHomeView.hpp"

class HomePresenter : public IHomePresenter {
public:
    explicit HomePresenter(IHomeView* view);
    void HandleLogout() override;

private:
    IHomeView* m_view;
};