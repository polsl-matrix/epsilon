#pragma once

#include "../../../../core/event/event.hpp"
#include <string>

namespace epsilon::features::registration {

class IRegistrationView {
public:
    virtual ~IRegistrationView() = default;
    virtual void ShowRegistrationError(const std::string &error) = 0;

    epsilon::core::event::Event<std::string, std::string, std::string> OnRegistrationRequested;
    epsilon::core::event::Event<> OnLoginLinkClicked;
};

}