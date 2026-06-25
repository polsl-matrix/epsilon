#pragma once

#include "../../../../core/event/event.hpp"
#include "message_dao.hpp"

#include <string>

namespace epsilon::features::chat_room {

class IChatRoomView {
public:
    virtual ~IChatRoomView() = default;
    virtual void AppendMessage(MessageDao message) = 0;
    virtual void PrependMessage(MessageDao message) = 0;
    virtual void SetRoomName(const std::string& name) = 0;
    virtual void SetRoomAvatar(const std::string& avatar) = 0;

    epsilon::core::event::Event<std::string> OnMessageSent;
    epsilon::core::event::Event<> OnLoadEarlierRequested;
};

}
