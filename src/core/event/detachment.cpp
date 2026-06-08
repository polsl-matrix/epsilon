#include "detachment.hpp"

epsilon::core::event::Detachment::Detachment(std::function<void()> detachAction)
    : m_DetachAction(detachAction) {}

void epsilon::core::event::Detachment::Detach() {
    if (m_DetachAction) {
        m_DetachAction();
        m_DetachAction = nullptr;
    }
}
