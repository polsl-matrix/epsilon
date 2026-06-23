#pragma once

#include <variant>
#include <concepts>
#include <type_traits>

namespace epsilon::util {

template <typename T, typename Variant>
struct is_alternative_of;

template <typename T, typename... Args>
struct is_alternative_of<T, std::variant<Args...>> 
    : std::disjunction<std::is_same<T, Args>...> {};

template <typename T, typename Variant>
concept alternative_of = is_alternative_of<T, Variant>::value;

} // namespace epsilon::util
