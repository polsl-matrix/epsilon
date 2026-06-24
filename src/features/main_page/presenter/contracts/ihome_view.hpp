#pragma once

#include "../../../../core/event/event.hpp"

namespace epsilon::features::home {

class IHomeView {
  public:
    virtual ~IHomeView() = default;
    virtual void ShowLogoutSuccess() = 0;

    core::event::Event<std::string> OnChatSelected;
    core::event::Event<> OnLogoutRequested;
};

}
