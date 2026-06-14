namespace epsilon::core::event {

template <typename... Args> Observer<Args...>::~Observer() = default;

template <typename... Args> void Observer<Args...>::Attached() {}

template <typename... Args> void Observer<Args...>::Detached() {}

} // namespace epsilon::core::event
