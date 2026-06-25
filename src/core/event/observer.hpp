#pragma once

// FIXME: The observer might get deleted WHILE updating,
// which may cause issues with longer callbacks.

namespace epsilon::core::event {
template <typename... Args> class Observer {
  public:
    virtual ~Observer() = default;

    virtual void Attached();

    virtual void Update(Args... args) = 0;
};
} // namespace epsilon::core::event

#include "observer.tpp"
