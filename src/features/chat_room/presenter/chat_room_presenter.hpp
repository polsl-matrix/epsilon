#pragma once

#include "../contracts/ichat_room_view.hpp"
#include "../../../core/event/detachment.hpp"
#include <memory>
#include <string>

namespace epsilon::features::chat_room::presenter {

class ChatRoomPresenter {
public:
    explicit ChatRoomPresenter(std::weak_ptr<IChatRoomView> view);
    void HandleSendMessage(const std::string& text);

private:
    std::weak_ptr<IChatRoomView> m_View;
    epsilon::core::event::Detachment m_MessageSentDetachment;
    epsilon::core::event::Detachment m_ViewReadyDetachment;
};

}