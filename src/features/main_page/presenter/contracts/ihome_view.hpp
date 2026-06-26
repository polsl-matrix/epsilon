#pragma once

#include "../../../../core/event/event.hpp"
#include "../../../chat_room/presenter/contracts/ichat_room_view.hpp"
#include "room_dto.hpp"

#include <memory>
#include <string>

namespace epsilon::features::home {

class IHomeView {
  public:
    virtual ~IHomeView() = default;
    
    virtual void ShowLogoutSuccess() = 0;
    virtual void SetRoomsList(const std::vector<RoomDto>& rooms) = 0;
    virtual void SetUserName(std::string user_name) = 0;

    virtual std::unique_ptr<chat_room::IChatRoomView> LoadChatRoomView() = 0;

    core::event::Event<std::string> OnChatSelected;
    core::event::Event<> OnLogoutRequested;
};

}
