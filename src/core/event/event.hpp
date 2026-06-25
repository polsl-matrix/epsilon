#pragma once

#include "observer.hpp"

#include <concepts>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace epsilon::core::event {
template <typename... Args> class Event {
    // TODO: Add some sort of a clean-up system for invalid observers
    std::vector<std::weak_ptr<Observer<Args...>>> m_Observers;

  public:
    Event();
    ~Event();

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    Event(Event&&) noexcept = default;
    Event& operator=(Event&&) noexcept = default;

    /// @brief Attaches an observer to be called when the event is invoked.
    /// The observer is detached automatically upon its destruction.
    void Attach(std::weak_ptr<Observer<Args...>> observer);

    template <std::derived_from<Observer<Args...>> TObserver,
              typename... ConstructorArgs>
        requires std::is_constructible_v<TObserver, ConstructorArgs &&...>
    std::shared_ptr<TObserver> Attach(ConstructorArgs &&...args);

    void Invoke(Args... args);
};
}

#include "event.tpp"