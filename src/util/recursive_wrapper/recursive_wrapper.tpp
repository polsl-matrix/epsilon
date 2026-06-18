#include "recursive_wrapper.hpp"

#include <memory>
#include <utility>

namespace epsilon::util {

template <typename T>
RecursiveWrapper<T>::RecursiveWrapper() 
    : m_Inner(std::make_unique<T>()) {}

template <typename T>
RecursiveWrapper<T>::RecursiveWrapper(const T& value) 
    : m_Inner(std::make_unique<T>(value)) {}

template <typename T>
RecursiveWrapper<T>::RecursiveWrapper(T&& value) 
    : m_Inner(std::make_unique<T>(std::move(value))) {}

template <typename T>
RecursiveWrapper<T>::RecursiveWrapper(const RecursiveWrapper& other) 
    : m_Inner(std::make_unique<T>(*other.m_Inner)) {}

template <typename T>
RecursiveWrapper<T>& RecursiveWrapper<T>::operator=(const RecursiveWrapper& other) {
    if (this != &other) {
        *m_Inner = *other.m_Inner;
    }
    return *this;
}

template <typename T>
T& RecursiveWrapper<T>::get() { 
    return *m_Inner; 
}

template <typename T>
const T& RecursiveWrapper<T>::get() const { 
    return *m_Inner; 
}

template <typename T>
RecursiveWrapper<T>::operator T&() { 
    return *m_Inner; 
}

template <typename T>
RecursiveWrapper<T>::operator const T&() const { 
    return *m_Inner; 
}

} // namespace epsilon::util
