#pragma once

#include "detachment.hpp"
#include "observer.hpp"

#include <concepts>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

namespace epsilon::core::event {
template <typename... Args> class Event {
    struct Slot {
        size_t id; // NOLINT(readability-identifier-length)
        std::shared_ptr<Observer<Args...>> observer;
    };

    std::vector<Slot> m_Observers;
    size_t m_NextId = 0;

  public:
    Event();
    ~Event();

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    Event(Event&&) noexcept = default;
    Event& operator=(Event&&) noexcept = default;

    Detachment Attach(std::shared_ptr<Observer<Args...>> observer);

    template <std::derived_from<Observer<Args...>> TObserver,
              typename... ConstructorArgs>
        requires std::is_constructible_v<TObserver, ConstructorArgs &&...>
    Detachment Attach(ConstructorArgs &&...args);

  private:
    void DetachById(size_t id); // NOLINT(readability-identifier-length)

  public:
    void Invoke(Args... args);
};
}

#include "event.tpp"