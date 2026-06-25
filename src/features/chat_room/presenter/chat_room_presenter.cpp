#include "chat_room_presenter.hpp"

#include "../../../core/event/util/action.hpp"
#include "../../../model/room.hpp"
#include "contracts/ichat_room_view.hpp"
#include "contracts/message_dao.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

namespace epsilon::features::chat_room {

ChatRoomPresenter::ChatRoomPresenter(std::shared_ptr<IChatRoomView> view,
                                     std::shared_ptr<model::Room> model,
                                     std::shared_ptr<model::Session> session)
    : m_View(std::move(view)), m_Model(std::move(model)),
      m_Session(std::move(session)), m_LoadedCount(0) {
    const auto room_name = m_Model->Name();
    const auto first_letter = std::string{ room_name[0] };

    m_View->SetRoomName(room_name);
    m_View->SetRoomAvatar(first_letter);

    m_MessageSentEventHandle =
        m_View->OnMessageSent.Attach<Action<std::string>>(
            [this](std::string text) { HandleSendMessage(text); });

    LoadMessages();
}

void ChatRoomPresenter::LoadMessages() {
    std::weak_ptr<IChatRoomView> view_weak_pointer = m_View;
    std::weak_ptr<model::Session> session_weak_pointer = m_Session;

    m_Model->MessageList()->Then([view_weak_pointer, session_weak_pointer](
                                     const model::Room::Result &result) {
        if (!result.has_value()) {
            std::cerr
                << "Failed to load initial message batch from room backend.\n";
            return;
        }

        const auto &messages_ptr = result.value();
        if (!messages_ptr) {
            return;
        }

        const auto &messages = *messages_ptr;

        if (auto session = session_weak_pointer.lock()) {
            auto current_user = session->CurrentUser();

            for (const auto &message : messages) {
                if (auto view = view_weak_pointer.lock()) {
                    view->AppendMessage(
                        MessageDao{ message.Author().Name(), message.Content(),
                                    message.Author() == current_user });
                }
            }
        } else {
            return;
        }
    });
}

void ChatRoomPresenter::HandleSendMessage(const std::string &text) {
    if (text.empty()) {
        return;
    }

    m_Model->SendMessage(text);
    m_LoadedCount++;

    m_View->AppendMessage(
        MessageDao{ m_Session->CurrentUser().Name(), text, true });
}

} // namespace epsilon::features::chat_room