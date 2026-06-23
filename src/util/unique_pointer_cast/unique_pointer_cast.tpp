#pragma once

#include "unique_pointer_cast.hpp"

#include <memory>
#include <concepts>

namespace epsilon::util {

template <typename TTarget, typename TFrom>
    requires std::derived_from<TFrom, TTarget>
std::unique_ptr<TTarget> unique_pointer_cast(std::unique_ptr<TFrom>&& old_ptr) {
    return std::unique_ptr<TTarget>(static_cast<TTarget*>(old_ptr.release()));
}

}
