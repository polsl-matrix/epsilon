#pragma once

#include "../observer.hpp"

#include <functional>

namespace epsilon::core::event::util {
template <typename... Args> class Action : Observer<Args...> {
    std::function<void(Args...)> m_Action;

  public:
    Action(std::function<void(Args...)> action) noexcept;
    Action(Action<Args...> &&other) noexcept;

    void Invoke(Args... args);
};
} // namespace epsilon::core::event::util
