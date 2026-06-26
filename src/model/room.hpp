#pragma once

#include "../services/matrix/requests/authenticated_request_manager.hpp"
#include "../core/event/event.hpp"
#include "../core/future/future.hpp"

#include "message.hpp"

#include <memory>
#include <string>
#include <vector>

namespace epsilon::model {

enum class GetMessagesError {
    RequestFailed,
    UnknownError
};

enum class SendMessageError {
    RequestFailed,
    Unauthorized,
    RoomNotFound,
    UnknownError
};

class Room {
    using RequestManager = services::matrix::requests::AuthenticatedRequestManager;

    std::shared_ptr<RequestManager> m_RequestManager;
    std::string m_Id;

public:
    using MessageVector = std::vector<Message>;
    using Result = std::expected<std::shared_ptr<MessageVector>, GetMessagesError>;

    Room(std::shared_ptr<RequestManager> request_manager, std::string id);

    Room(Room&&) noexcept = default; 
    Room& operator=(Room&&) noexcept = default;

    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;

    std::string Id() const;
    std::string Name() const;
    std::shared_ptr<typename core::future::Future<Result>::Handle> MessageList() const;

    std::shared_ptr<core::future::Future<std::expected<void, SendMessageError>>::Handle> SendMessage(std::string content);

    core::event::Event<> OnMessageReceived;
};

}