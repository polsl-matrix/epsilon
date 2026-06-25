#pragma once

#include "contracts/ichat_room_view.hpp"
#include "../../../model/room.hpp"
#include "../../../model/session.hpp"
#include "../../../core/event/detachment.hpp"

#include <memory>
#include <string>
#include <vector>

namespace epsilon::features::chat_room {

class ChatRoomPresenter {
    std::shared_ptr<IChatRoomView> m_View;
    std::shared_ptr<model::Room> m_Model;
    std::shared_ptr<model::Session> m_Session;
    
    epsilon::core::event::Detachment m_MessageSentDetachment;
    epsilon::core::event::Detachment m_LoadEarlierDetachment;
    
    int m_LoadedCount;
    
public:
    explicit ChatRoomPresenter(
        std::shared_ptr<IChatRoomView> view,
        std::shared_ptr<model::Room> model,
        std::shared_ptr<model::Session> session
    );
    ~ChatRoomPresenter();

    void HandleSendMessage(const std::string& text);

private:
    void LoadInitialBatch();
    void LoadEarlierBatch();
};

}