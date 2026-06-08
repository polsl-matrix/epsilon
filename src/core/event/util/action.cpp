#include "action.hpp"

#include <utility>

template <typename... Args>
epsilon::core::event::util::Action<Args...>::Action(
    std::function<void(Args...)> action)
    : m_Action(std::move(action)) {}

template <typename... Args>
epsilon::core::event::util::Action<Args...>::Action(Action<Args...> &&other)
    : m_Action(std::move(other.m_Action)) {}

template <typename... Args>
void epsilon::core::event::util::Action<Args...>::Invoke(Args... args) {
    m_Action(args...);
}
