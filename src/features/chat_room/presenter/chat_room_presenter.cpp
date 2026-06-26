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
      m_Session(std::move(session)) {
    const auto room_name = m_Model->Name();
    const std::string first_letter{ room_name[0] };

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

        const auto messages = result.value();
        if (!messages) {
            return;
        }

        if (auto session = session_weak_pointer.lock()) {
            session->CurrentUser()->Then(
                [view_weak_pointer,
                 messages = std::move(messages)](const auto &current_user) {
                    if (!current_user.has_value()) {
                        if (auto view = view_weak_pointer.lock()) {
                            view->AppendMessage(
                                MessageDao{ "epsilon",
                                            "We've encountered some problems "
                                            "while loading messages :(",
                                            false });
                        }
                        return;
                    }

                    for (const auto &message : *messages) {
                        message.Author().Name()->Then(
                            [view_weak_pointer, message, current_user,
                             messages](const auto &author_name) {
                                if (auto view = view_weak_pointer.lock()) {
                                    view->AppendMessage(MessageDao{
                                        author_name, message.Content(),
                                        message.Author() == *current_user });
                                }
                            });
                    }
                });
        } else {
            return;
        }
    });
}

void ChatRoomPresenter::HandleSendMessage(const std::string &text) {
    if (text.empty()) {
        return;
    }

    std::weak_ptr<IChatRoomView> view_weak_pointer = m_View;
    std::weak_ptr<model::Session> session_weak_pointer = m_Session;

    m_Model->SendMessage(text)->Then(
        [view_weak_pointer, session_weak_pointer, text](const auto &reply) {
            if (!reply) {
                if (auto view = view_weak_pointer.lock()) {
                    view->AppendMessage(
                        MessageDao{ "epsilon", "Failed to send :(", false });
                }
                return;
            }

            if (auto session = session_weak_pointer.lock()) {
                session->CurrentUser()->Then(
                    [view_weak_pointer, text](const auto &current_user) {
                        if (!current_user.has_value()) {
                            if (auto view = view_weak_pointer.lock()) {
                                view->AppendMessage(MessageDao{
                                    "epsilon", "Failed to send :(", false });
                            }
                            return;
                        }

                        current_user->Name()->Then(
                            [view_weak_pointer, text](const auto &user_name) {
                                if (auto view = view_weak_pointer.lock()) {
                                    view->AppendMessage(
                                        MessageDao{ user_name, text, true });
                                }
                            });
                    });
            }
        });
}

} // namespace epsilon::features::chat_room