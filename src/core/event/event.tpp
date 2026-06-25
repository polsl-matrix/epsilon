#pragma once

#include "event.hpp"

#include "observer.hpp"

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace epsilon::core::event {

template <typename... Args> Event<Args...>::Event() = default;
template <typename... Args> Event<Args...>::~Event() = default;

template <typename... Args>
void Event<Args...>::Attach(std::weak_ptr<Observer<Args...>> observer) {
    auto observer_lock = observer.lock();

    if(!observer_lock) {
        throw std::invalid_argument("Can't attach an invalid (nullptr) observer!");
    }

    auto present = std::find_if(m_Observers.begin(), m_Observers.end(), [&observer_lock](std::weak_ptr<Observer<Args...>> other) {
        if(auto other_lock = other.lock()) {
            return observer_lock.get() == other_lock.get();
        }

        return false;
    });

    if (present != m_Observers.end()) {
        throw std::runtime_error(
            "Can't attach the same observer twice to the same event!");
    }

    m_Observers.push_back(observer);

    observer_lock->Attached();
}

template <typename... Args>
template <std::derived_from<Observer<Args...>> TObserver, typename... ConstructorArgs>
    requires std::is_constructible_v<TObserver, ConstructorArgs &&...>
std::shared_ptr<TObserver> Event<Args...>::Attach(ConstructorArgs &&...args) {
    const auto observer = std::make_shared<TObserver>(std::forward<ConstructorArgs>(args)...);

    Attach(observer);

    return observer;
}

template <typename... Args> void Event<Args...>::Invoke(Args... args) {
    for (auto &observer : m_Observers) {
        if(std::shared_ptr<Observer<Args...>> observer_lock = observer.lock()) {
            observer_lock->Update(args...);
        }
    }
}

}