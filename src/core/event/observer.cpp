#include "observer.hpp"

namespace epsilon::core::event {

template <typename... Args> void Observer<Args...>::Attached() {}

template <typename... Args> void Observer<Args...>::Detached() {}

} // namespace epsilon::core::event
