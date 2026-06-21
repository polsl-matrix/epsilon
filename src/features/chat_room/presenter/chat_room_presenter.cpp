#include "chat_room_presenter.hpp"
#include "../../../core/event/util/action.hpp"
#include <algorithm>

namespace epsilon::features::chat_room::presenter {

ChatRoomPresenter::ChatRoomPresenter(std::weak_ptr<IChatRoomView> view)
    : m_View(std::move(view)),
      m_MessageSentDetachment([]() {}),
      m_ViewReadyDetachment([]() {}),
      m_LoadEarlierDetachment([]() {}),
      m_LoadedCount(0) {

    m_Database = {
        {"Hey! Are we still working on the epsilon architecture?", false},
        {"Yes, backend is fully detached now. Working on the chat UI.", true},
        {"Awesome. The custom event system is extremely fast.", false},
        {"Did you check the new CMake configuration?", true},
        {"Everything compiles without any warnings or errors.", false},
        {"Great! Now let's test how the scrolling behaves with many messages.", true},
        {"Adding a few more lines to fill up the screen completely.", false},
        {"This should push the top messages under the fading overlay.", true},
        {"Looks really clean, exactly like iMessage.", false},
        {"We also need animations for the send button and the header.", true},
        {"And replacing the text arrow with an SVG icon.", false},
        {"Now testing the refined top gradient overlay.", true},
        {"It uses pure alpha channel interpolation to avoid gray smudges.", false},
        {"And the scrollbar appears dynamically only while moving.", true}
    };

    if (auto view = m_View.lock()) {
        m_MessageSentDetachment = view->OnMessageSent.template Attach<
            epsilon::core::event::util::Action<std::string>>(
            [this](std::string text) {
                HandleSendMessage(text);
            });

        m_ViewReadyDetachment = view->OnViewReady.template Attach<
            epsilon::core::event::util::Action<>>(
            [this]() {
                LoadInitialBatch();
            });

        m_LoadEarlierDetachment = view->OnLoadEarlierRequested.template Attach<
            epsilon::core::event::util::Action<>>(
            [this]() {
                LoadEarlierBatch();
            });
    }
}

void ChatRoomPresenter::LoadInitialBatch() {
    if (auto view = m_View.lock()) {
        const int batch_size = 7;
        const int total = static_cast<int>(m_Database.size());
        const int start = std::max(0, total - batch_size);

        for (int i = start; i < total; ++i) {
            view->AppendMessage(m_Database[i].text, m_Database[i].is_me);
        }
        m_LoadedCount = total - start;
    }
}

void ChatRoomPresenter::LoadEarlierBatch() {
    if (auto view = m_View.lock()) {
        const int total = static_cast<int>(m_Database.size());
        if (m_LoadedCount >= total) {
            return;
        }

        const int batch_size = 7;
        const int end = total - m_LoadedCount;
        const int start = std::max(0, end - batch_size);

        for (int i = end - 1; i >= start; --i) {
            view->PrependMessage(m_Database[i].text, m_Database[i].is_me);
        }
        m_LoadedCount += (end - start);
    }
}

void ChatRoomPresenter::HandleSendMessage(const std::string& text) {
    if (text.empty()) {
        return;
    }
    m_Database.push_back({text, true});
    m_LoadedCount++;
    if (auto view = m_View.lock()) {
        view->AppendMessage(text, true);
    }
}

}