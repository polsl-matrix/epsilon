#include "detachment.hpp"

#include <functional>
#include <utility>

namespace epsilon::core::event {

Detachment::Detachment(std::function<void()> detachAction) noexcept
    : m_DetachAction(std::move(detachAction)) {}

void Detachment::Detach() {
    if (m_DetachAction) {
        m_DetachAction();
        m_DetachAction = nullptr;
    }
}

} // namespace epsilon::core::event
