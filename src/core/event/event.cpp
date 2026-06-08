#include "event.hpp"

#include <algorithm>

template <typename... Args>
epsilon::core::event::Event<Args...>::Event() = default;

template <typename... Args> epsilon::core::event::Event<Args...>::~Event() {
    for (auto &slot : m_Observers) {
        slot.observer->Detached();
    }
}

template <typename... Args>
epsilon::core::event::Detachment epsilon::core::event::Event<Args...>::Attach(
    std::unique_ptr<Observer<Args...>> &&observer) {
    size_t id = m_NextId;
    m_NextId++;

    m_Observers.push_back({id, observer});

    observer->Attached();

    return Detachment([this, id]() { this->DetachById(id); });
}

template <typename... Args>
void epsilon::core::event::Event<Args...>::DetachById(size_t id) {
    auto slot_iterator =
        std::find_if(m_Observers.begin(), m_Observers.end(),
                     [id](auto slot) { return slot.id == id; });

    slot_iterator->observer->Detached();

    m_Observers.erase(slot_iterator);
}
