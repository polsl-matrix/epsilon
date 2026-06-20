#pragma once

#include <memory>
#include <utility>

namespace epsilon::util {

template <typename T>
class RecursiveWrapper {
private:
    std::unique_ptr<T> m_Inner;

public:
    RecursiveWrapper();
    RecursiveWrapper(const T& value);
    RecursiveWrapper(T&& value);
    
    RecursiveWrapper(const RecursiveWrapper& other);
    RecursiveWrapper& operator=(const RecursiveWrapper& other);
    RecursiveWrapper(RecursiveWrapper&&) noexcept = default;
    RecursiveWrapper& operator=(RecursiveWrapper&&) noexcept = default;

    T& get();
    const T& get() const;
    
    operator T&();
    operator const T&() const;
};

} // namespace epsilon::util

#include "recursive_wrapper.tpp"
