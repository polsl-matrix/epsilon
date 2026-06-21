#pragma once

#include "../../../core/event/event.hpp"
#include <string>

class IChatRoomView {
public:
    virtual ~IChatRoomView() = default;
    virtual void AppendMessage(const std::string& text, bool isMe) = 0;
    virtual void PrependMessage(const std::string& text, bool isMe) = 0;
    epsilon::core::event::Event<std::string> OnMessageSent;
    epsilon::core::event::Event<> OnViewReady;
    epsilon::core::event::Event<> OnLoadEarlierRequested;
};