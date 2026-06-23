#pragma once

#include "future.hpp"

#include "../event/event.hpp"
#include "../event/util/action.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>

namespace epsilon::core::future {

template <typename TValue>
void Future<TValue>::FutureObserver::Then(std::function<void(TValue)> callback) {
    if(m_Value.has_value()) {
        callback(*m_Value);
    }

    m_Callback = callback;
}

template <typename TValue>
void Future<TValue>::FutureObserver::Update(TValue value) {
    m_Value = value;

    if(m_Callback.has_value()) {
        (*m_Callback)(value);
    }
}

template <typename TValue>
void Future<TValue>::Realize(TValue value) {
    if(m_CachedValue.has_value()) {
        throw std::runtime_error("Cannot realize the same future twice!");
    }

    m_Finished.Invoke(value);
    m_CachedValue = value;
}

template <typename TValue>
std::shared_ptr<typename Future<TValue>::Handle> Future<TValue>::GetHandle() {
    const auto observer = std::make_shared<FutureObserver>();

    if(m_CachedValue.has_value()) {
        observer->Update(*m_CachedValue);
    }

    m_Finished.Attach(observer);

    return observer;
}

};
