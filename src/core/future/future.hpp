#pragma once

#include "../event/event.hpp"
#include "../event/observer.hpp"

#include <functional>
#include <optional>
#include <memory>

namespace epsilon::core::future {

template <typename TValue> class Future {
    template<typename T>
    using Event = event::Event<T>;

    std::optional<TValue> m_CachedValue = std::nullopt;
    Event<const TValue&> m_Finished;
    
  public:
    class Handle {
      public:
      virtual void Then(std::function<void(const TValue&)>) = 0;
    };
    
  private:
    // Necessary to keep the handles alive as long as the future is active
    std::vector<std::shared_ptr<Handle>> m_Handles;

    class FutureObserver : public event::Observer<const TValue&>, public Handle {
        std::optional<TValue> m_Value = std::nullopt;
        std::optional<std::function<void(const TValue&)>> m_Callback = std::nullopt;

      public:
        virtual void Then(std::function<void(const TValue&)> callback) override;

        virtual void Update(const TValue& value) override;
    };

  public:
    void Realize(TValue&& value);

    std::shared_ptr<Handle> GetHandle();
};

}

#include "future.tpp"
