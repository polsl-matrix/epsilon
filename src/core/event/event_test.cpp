#include "event.hpp"
#include "observer.hpp"
#include "util/action.hpp"

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>

using epsilon::core::event::Event;
using epsilon::core::event::Observer;
using epsilon::core::event::util::Action;

class MockCountObserver : public Observer<> {
    size_t m_UpdateCount = 0;
    size_t m_AttachmentCount = 0;
    size_t m_DetachmentCount = 0;

public:
    virtual void Attached() override {
        m_AttachmentCount++;
    }

    virtual void Detached() override {
        m_DetachmentCount++;
    }

    virtual void Update() override {
        m_UpdateCount++;
    }

    size_t GetAttachmentCount() const {
        return m_AttachmentCount;
    }

    size_t GetDetachmentCount() const {
        return m_DetachmentCount;
    }

    size_t GetUpdateCount() const {
        return m_UpdateCount;
    }
};

TEST(EventTests, EventFiring) {
    uint32_t state = 0;
    Event<uint32_t> event;
    
    event.Attach<Action<uint32_t>>([&state](uint32_t new_state) {
        state = new_state;
    });
    
    const uint32_t new_state = 42;

    event.Invoke(new_state);

    EXPECT_EQ(state, new_state);
}

TEST(EventTests, ObserverMethodsProperlyCalled) {
    Event<> event;
    auto observer = std::make_shared<MockCountObserver>();
    
    event.Invoke();
    
    EXPECT_EQ(observer->GetUpdateCount(), 0);
    
    auto detachment = event.Attach(std::static_pointer_cast<Observer<>>(observer));
    
    EXPECT_EQ(observer->GetAttachmentCount(), 1);
    
    event.Invoke();
    
    EXPECT_EQ(observer->GetUpdateCount(), 1);

    event.Invoke();
    
    EXPECT_EQ(observer->GetUpdateCount(), 2);
    
    detachment.Detach();

    EXPECT_EQ(observer->GetDetachmentCount(), 1);

    event.Invoke();
    
    EXPECT_EQ(observer->GetUpdateCount(), 2);
}

TEST(EventTests, DisallowAttachingObserverToEventTwice) {
    Event<> event;
    auto observer = std::make_shared<Action<>>([]() {});

    event.Attach(observer);

    EXPECT_THROW({
        event.Attach(observer);
    }, std::runtime_error);
}
