#pragma once

#include "../observer.hpp"

#include <functional>

namespace epsilon::core::event::util {
template <typename... Args> class Action : Observer<Args...> {
    std::function<void(Args...)> m_Action;

  public:
    Action(std::function<void(Args...)>);
    Action(Action<Args...> &&);

    void Invoke(Args...);
};
} // namespace epsilon::core::event::util
