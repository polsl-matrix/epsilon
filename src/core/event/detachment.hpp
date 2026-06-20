#pragma once

#include <functional>

namespace epsilon::core::event {
class Detachment {
  private:
    std::function<void()> m_DetachAction;

  public:
    Detachment(std::function<void()> detachAction) noexcept;

    void Detach();
};
} // namespace epsilon::core::event
