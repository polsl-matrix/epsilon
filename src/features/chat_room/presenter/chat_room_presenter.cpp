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

    LoadInitialBatch();

    m_LoadEarlierEventHandle = m_View->OnLoadEarlierRequested.Attach<Action<>>(
        [this]() { LoadEarlierBatch(); });
}

void ChatRoomPresenter::LoadInitialBatch() {
    m_Model->MessageList()->Then([this](const model::Room::Result &result) {
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
        const int batch_size = 7;
        const int total = static_cast<int>(messages.size());
        const int start = std::max(0, total - batch_size);

        for (int i = start; i < total; ++i) {
            m_View->AppendMessage(
                MessageDao{ messages[i].Author().Name(), messages[i].Content(),
                            messages[i].Author() == m_Session->CurrentUser() });
        }
        m_LoadedCount = total - start;
    });
}

void ChatRoomPresenter::LoadEarlierBatch() {
    return;
    m_Model->MessageList()->Then([this](const model::Room::Result &result) {
        if (!result.has_value()) {
            std::cerr
                << "Failed to load earlier message batch from room backend.\n";
            return;
        }

        const auto &messages_ptr = result.value();
        if (!messages_ptr) {
            return;
        }

        const auto &messages = *messages_ptr;
        const int total = static_cast<int>(messages.size());
        if (m_LoadedCount >= total) {
            return;
        }

        const int batch_size = 7;
        const int end = total - m_LoadedCount;
        const int start = std::max(0, end - batch_size);

        for (int i = end - 1; i >= start; --i) {
            m_View->PrependMessage(
                MessageDao{ messages[i].Author().Name(), messages[i].Content(),
                            messages[i].Author() == m_Session->CurrentUser() });
        }
        m_LoadedCount += (end - start);
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