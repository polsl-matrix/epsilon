#pragma once

#include "../services/matrix/requests/authenticated_request_manager.hpp"
#include "../core/event/event.hpp"

#include "message.hpp"

#include <memory>
#include <string>
#include <vector>

namespace epsilon::model {

class Room {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;

    std::shared_ptr<RequestManager> m_RequestManager;

    std::string m_Id;

    std::vector<Message> m_Messages; // This is temporary - to be replaced by backend

public:
    Room(std::shared_ptr<RequestManager> request_manager, std::string id);

    Room(Room&&) noexcept = default; 
    Room& operator=(Room&&) noexcept = default;

    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    std::string Id() const;
    std::string Name() const;
    std::vector<Message> MessageList() const;

    void SendMessage(std::string content);

    core::event::Event<> OnMessageReceived;
};

}