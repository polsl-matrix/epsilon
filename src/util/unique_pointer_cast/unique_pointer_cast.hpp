#pragma once

#include <memory>

namespace epsilon::util {

template <typename TTarget, typename TFrom>
    requires std::derived_from<TFrom, TTarget>
std::unique_ptr<TTarget> unique_pointer_cast(std::unique_ptr<TFrom>&& old_ptr);

}

#include "unique_pointer_cast.tpp"
