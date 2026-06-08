#pragma once

#include "detachment.hpp"
#include "observer.hpp"

#include <memory>
#include <vector>

namespace epsilon::core::event {
template <typename... Args> class Event {
    struct Slot {
        size_t id; // NOLINT(readability-identifier-length)
        std::unique_ptr<Observer<Args...>> observer;
    };

    std::vector<Slot> m_Observers;
    size_t m_NextId = 0;

  public:
    Event();
    ~Event();

    Detachment Attach(std::unique_ptr<Observer<Args...>> &&observer);

  private:
    void DetachById(size_t id); // NOLINT(readability-identifier-length)

  public:
    void Invoke(Args... args);
};
} // namespace epsilon::core::event
