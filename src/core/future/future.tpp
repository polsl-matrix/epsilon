#pragma once

#include "future.hpp"

#include "../event/event.hpp"
#include "../event/util/action.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <utility>

namespace epsilon::core::future {

template <typename TValue>
Future<TValue>::Handle& Future<TValue>::FutureObserver::Then(std::function<void(const TValue&)> callback) {
    if(m_Callback.has_value()) {
        auto prev_callback = m_Callback.value();

        m_Callback = [prev_callback, callback](const TValue& argument) {
            prev_callback(argument);

            callback(argument);
        };
    } else {
        m_Callback = callback;
    }

    if(m_Value.has_value()) {
        Update(*m_Value);
    }

    return *this;
}

template <typename TValue>
Future<TValue>::Handle& Future<TValue>::FutureObserver::After(std::shared_ptr<Handle> other) {
    if(m_Lock.has_value()) {
        throw std::runtime_error("Only linear 'after' chains are supported");
    }

    m_Lock = other;

    return *this;
}

template <typename TValue>
bool Future<TValue>::FutureObserver::Realized() const {
    return m_Value.has_value();
}

template <typename TValue>
void Future<TValue>::FutureObserver::Update(const TValue& value) {
    if(m_Lock.has_value()) {
        if(!m_Lock.value()->Realized()) {
            // FIXME: This might crash the app if the "after" handle gets destroyed before the
            // "before" handle gets executed
            m_Lock.value()->Then([this, value](const TValue&) {
                m_Value = value;

                if(m_Callback.has_value()) {
                    m_Callback.value()(value);
                }
            });

            return;
        }
    }
    
    m_Value = value;

    if(m_Callback.has_value()) {
        (*m_Callback)(value);
    }
}

template <typename TValue>
void Future<TValue>::Realize(TValue&& value) {
    if(m_CachedValue.has_value()) {
        throw std::runtime_error("Cannot realize the same future twice!");
    }

    m_Finished.Invoke(value);
    m_CachedValue = std::move(value);
}

template <typename TValue>
std::shared_ptr<typename Future<TValue>::Handle> Future<TValue>::GetHandle() {
    const auto observer = std::make_shared<FutureObserver>();

    if(m_CachedValue.has_value()) {
        observer->Update(*m_CachedValue);
    }

    m_Finished.Attach(observer);
    
    m_Handles.push_back(observer);

    return observer;
}

} // namespace epsilon::core::future