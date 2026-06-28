#include "room.hpp"

#include "../services/matrix/requests/authenticated_request_manager.hpp"
#include "../services/matrix/requests/implementation/common/empty.hpp"
#include "../services/matrix/requests/implementation/common/error.hpp"
#include "../services/matrix/requests/implementation/room_messages/room_messages_request.hpp"
#include "../services/matrix/requests/implementation/send_message/send_message_request.hpp"
#include "../services/matrix/requests/implementation/send_message/send_message_request_body.hpp"
#include "../services/matrix/requests/implementation/send_message/send_message_request_response.hpp"

#include "message.hpp"
#include "user.hpp"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace epsilon::model {

Room::Room(std::shared_ptr<RequestManager> request_manager, std::string id)
    : m_RequestManager(std::move(request_manager)), m_Id(std::move(id)) {}

std::string Room::Id() const { return m_Id; }

std::string Room::Name() const {
    std::string name = "";

    for (size_t i = 1; i < 9 && i < m_Id.size(); i++) {
        name += m_Id[i];
    }

    return name;
}

std::shared_ptr<typename core::future::Future<Room::Result>::Handle>
Room::MessageList() const {
    using namespace epsilon::services::matrix::requests::implementation::
        room_messages;
    using namespace epsilon::services::matrix::requests::implementation::common;

    auto messages_future = std::make_shared<core::future::Future<Result>>();

    auto request = RoomMessagesRequest(m_Id);
    request.SetBody(Empty{});

    m_RequestManager->Execute<Empty, RoomMessagesRequestResponse, Error>(
        request,
        [request_manager = m_RequestManager, messages_future](auto reply) {
            if (!reply.has_value()) {
                messages_future->Realize(
                    std::unexpected(GetMessagesError::RequestFailed));
                return;
            }

            if (reply->StatusCode != 200 || !reply->Body.has_value()) {
                messages_future->Realize(
                    std::unexpected(GetMessagesError::UnknownError));
                return;
            }

            const auto &response_data = reply->Body.value();

            auto messages_vector = std::make_shared<std::vector<Message>>();
            messages_vector->reserve(response_data.Messages.size());

            for (const auto &msg_data : response_data.Messages) {
                User sender(request_manager, msg_data.Sender);
                messages_vector->emplace_back(std::move(sender), msg_data.Body, msg_data.Timestamp);
            }

            std::sort(messages_vector->begin(), messages_vector->end(), [](const auto &first, const auto &second) {
                return first.Timestamp() < second.Timestamp();
            });

            messages_future->Realize(std::move(messages_vector));
        });

    return messages_future->GetHandle();
}

std::shared_ptr<
    core::future::Future<std::expected<void, SendMessageError>>::Handle>
Room::SendMessage(std::string content) {
    using namespace epsilon::services::matrix::requests::implementation::
        send_message;
    using namespace epsilon::services::matrix::requests::implementation::common;

    auto result = std::make_shared<
        core::future::Future<std::expected<void, SendMessageError>>>();

    auto request = SendMessageRequest(m_Id);

    request.SetBody(SendMessageRequestBody(content));

    m_RequestManager->Execute<SendMessageRequestBody,
                              SendMessageRequestResponse,
                              Error>(request, [result](const auto &reply) {
        if (!reply) {
            result->Realize(std::unexpected(SendMessageError::RequestFailed));
            return;
        }

        if (reply->StatusCode == 400) {
            result->Realize(std::unexpected(SendMessageError::Unauthorized));
            return;
        }

        if (reply->StatusCode == 404) {
            result->Realize(std::unexpected(SendMessageError::RoomNotFound));
            return;
        }

        if (reply->StatusCode != 200 || !reply->Body.has_value()) {
            result->Realize(std::unexpected(SendMessageError::UnknownError));
            return;
        }

        result->Realize({});
    });

    return result->GetHandle();
}

} // namespace epsilon::model