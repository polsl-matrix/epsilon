#pragma once

#include "event.hpp"

#include "detachment.hpp"
#include "observer.hpp"

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace epsilon::core::event {

template <typename... Args> Event<Args...>::Event() = default;

template <typename... Args> Event<Args...>::~Event() {
    for (auto &slot : m_Observers) {
        slot.observer->Detached();
    }
}

template <typename... Args>
Detachment Event<Args...>::Attach(std::shared_ptr<Observer<Args...>> observer) {
    auto present = std::find_if(
        m_Observers.begin(), m_Observers.end(),
        [observer](const auto &slot) { return slot.observer == observer; });

    if (present != m_Observers.end()) {
        throw std::runtime_error(
            "Can't attach the same observer twice to the same event!");
    }

    auto id = m_NextId; // NOLINT(readability-identifier-length)
    m_NextId++;

    m_Observers.push_back({id, observer});

    observer->Attached();

    return Detachment([this, id]() { this->DetachById(id); });
}

template <typename... Args>
template <std::derived_from<Observer<Args...>> TObserver, typename... ConstructorArgs>
    requires (std::is_constructible_v<TObserver, ConstructorArgs &&...>)
Detachment Event<Args...>::Attach(ConstructorArgs &&...args) {
    return Attach(std::static_pointer_cast<Observer<Args...>>(
        std::make_shared<TObserver>(std::forward<ConstructorArgs>(args)...)));
}

template <typename... Args>
void Event<Args...>::DetachById(
    size_t id) { // NOLINT(readability-identifier-length)
    auto slot_iterator =
        std::find_if(m_Observers.begin(), m_Observers.end(),
                     [id](const auto &slot) { return slot.id == id; });

    slot_iterator->observer->Detached();

    m_Observers.erase(slot_iterator);
}

template <typename... Args> void Event<Args...>::Invoke(Args... args) {
    for (const auto &slot : m_Observers) {
        slot.observer->Update(args...);
    }
}

}