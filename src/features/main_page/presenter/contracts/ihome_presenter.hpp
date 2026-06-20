#pragma once

namespace epsilon::features::home {

class IHomePresenter {
  public:
    virtual ~IHomePresenter() = default;
    virtual void HandleLogout() = 0;
};

}
