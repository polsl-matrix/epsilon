#pragma once

#include "observer.hpp"

namespace epsilon::core::event {

template <typename... Args> void Observer<Args...>::Attached() {}

} // namespace epsilon::core::event
