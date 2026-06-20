#pragma once

class IHomePresenter {
  public:
    virtual ~IHomePresenter() = default;
    virtual void HandleLogout() = 0;
};