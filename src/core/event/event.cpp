#include "event.hpp"

#include "detachment.hpp"
#include "observer.hpp"

#include <algorithm>
#include <cstddef>
#include <memory>

namespace epsilon::core::event {

template <typename... Args> Event<Args...>::Event() = default;

template <typename... Args> Event<Args...>::~Event() {
    for (auto &slot : m_Observers) {
        slot.observer->Detached();
    }
}

template <typename... Args>
Detachment
Event<Args...>::Attach(std::unique_ptr<Observer<Args...>> &&observer) {
    size_t id = m_NextId; // NOLINT(readability-identifier-length)
    m_NextId++;

    m_Observers.push_back({id, observer});

    observer->Attached();

    return Detachment([this, id]() { this->DetachById(id); });
}

template <typename... Args>
void Event<Args...>::DetachById(
    size_t id) { // NOLINT(readability-identifier-length)
    auto slot_iterator =
        std::find_if(m_Observers.begin(), m_Observers.end(),
                     [id](auto slot) { return slot.id == id; });

    slot_iterator->observer->Detached();

    m_Observers.erase(slot_iterator);
}

} // namespace epsilon::core::event
