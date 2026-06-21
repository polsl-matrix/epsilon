#include "chat_room_presenter.hpp"
#include "../../../core/event/util/action.hpp"
#include <memory>
#include <string>

namespace epsilon::features::chat_room::presenter {

ChatRoomPresenter::ChatRoomPresenter(std::weak_ptr<IChatRoomView> view)
    : m_View(std::move(view)), m_MessageSentDetachment([]() {}), m_ViewReadyDetachment([]() {}) {
    if (auto view_ptr = m_View.lock()) {
        m_MessageSentDetachment = view_ptr->OnMessageSent.template Attach<
            epsilon::core::event::util::Action<std::string>>(
            [this](std::string text) {
                HandleSendMessage(text);
            });

        m_ViewReadyDetachment = view_ptr->OnViewReady.template Attach<
            epsilon::core::event::util::Action<>>(
            [this]() {
                if (auto v = m_View.lock()) {
                    v->AppendMessage("Hey! Are we still working on the epsilon architecture?", false);
                    v->AppendMessage("Yes, backend is fully detached now. Working on the chat UI.", true);
                    v->AppendMessage("Awesome. The custom event system is extremely fast.", false);
                    v->AppendMessage("Did you check the new CMake configuration?", true);
                    v->AppendMessage("Everything compiles without any warnings or errors.", false);
                    v->AppendMessage("Great! Now let's test how the scrolling behaves with many messages.", true);
                    v->AppendMessage("Adding a few more lines to fill up the screen completely.", false);
                    v->AppendMessage("This should push the top messages under the fading overlay.", true);
                    v->AppendMessage("Looks really clean, exactly like iMessage.", false);
                    v->AppendMessage("We also need animations for the send button and the header.", true);
                    v->AppendMessage("And replacing the text arrow with an SVG icon.", false);
                    v->AppendMessage("Now testing the refined top gradient overlay.", true);
                    v->AppendMessage("It uses pure alpha channel interpolation to avoid gray smudges.", false);
                    v->AppendMessage("And the scrollbar appears dynamically only while moving.", true);
                }
            });
    }
}

void ChatRoomPresenter::HandleSendMessage(const std::string& text) {
    if (text.empty()) {
        return;
    }
    if (auto view_ptr = m_View.lock()) {
        view_ptr->AppendMessage(text, true);
    }
}

}