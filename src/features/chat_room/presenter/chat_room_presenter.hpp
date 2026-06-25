#pragma once

#include "contracts/ichat_room_view.hpp"
#include "../../../model/room.hpp"
#include "../../../model/session.hpp"
#include "../../../core/event/util/action.hpp"

#include <memory>
#include <string>
#include <vector>

namespace epsilon::features::chat_room {

class ChatRoomPresenter {
    std::shared_ptr<IChatRoomView> m_View;
    std::shared_ptr<model::Room> m_Model;
    std::shared_ptr<model::Session> m_Session;
    
    template<typename... T>
    using Action = core::event::util::Action<T...>;

    std::shared_ptr<Action<std::string>> m_MessageSentEventHandle;
    std::shared_ptr<Action<>> m_LoadEarlierEventHandle;
    
    int m_LoadedCount;
    
public:
    explicit ChatRoomPresenter(
        std::shared_ptr<IChatRoomView> view,
        std::shared_ptr<model::Room> model,
        std::shared_ptr<model::Session> session
    );

    void HandleSendMessage(const std::string& text);

private:
    void LoadInitialBatch();
    void LoadEarlierBatch();
};

}