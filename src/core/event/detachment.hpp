#pragma once

#include <functional>

namespace epsilon::core::event {
class Detachment {
  private:
    std::function<void()> m_DetachAction;

  public:
    Detachment() = default;
    Detachment(std::function<void()> detachAction) noexcept;

    /// @brief Detaches the observer from an event.
    /// You should NEVER detach from an event which went out of scope.
    void Detach();
};
} // namespace epsilon::core::event
