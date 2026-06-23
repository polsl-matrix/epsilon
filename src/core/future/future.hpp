#pragma once

#include "../event/event.hpp"
#include "../event/observer.hpp"

#include <functional>
#include <optional>

namespace epsilon::core::future {

template <typename TValue> class Future {
    template<typename T>
    using Event = event::Event<T>;

    std::optional<TValue> m_CachedValue = std::nullopt;
    Event<TValue> m_Finished;
    
  public:
    class Handle {
      public:
        virtual void Then(std::function<void(TValue)>) = 0;
    };

  private:
    class FutureObserver : public event::Observer<TValue>, public Handle {
        std::optional<TValue> m_Value = std::nullopt;
        std::optional<std::function<void(TValue)>> m_Callback = std::nullopt;

      public:
        virtual void Then(std::function<void(TValue)>) override;

        virtual void Update(TValue value) override;
    };

  public:
    void Realize(TValue value);

    std::shared_ptr<Handle> GetHandle();
};

}

#include "future.tpp"
