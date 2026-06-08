#include "action.hpp"

#include <functional>
#include <utility>

namespace epsilon::core::event::util {

template <typename... Args>
Action<Args...>::Action(std::function<void(Args...)> action) noexcept
    : m_Action(std::move(action)) {}

template <typename... Args>
Action<Args...>::Action(Action<Args...> &&other) noexcept
    : m_Action(std::move(other.m_Action)) {}

template <typename... Args> void Action<Args...>::Invoke(Args... args) {
    m_Action(args...);
}

} // namespace epsilon::core::event::util
