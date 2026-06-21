#include "page_router.hpp"
#include "../features/chat_room/view/chat_room_view.hpp"
#include "../features/chat_room/presenter/chat_room_presenter.hpp"

PageRouter::PageRouter(QQmlContext* qmlContext, QObject* parent)
    : QObject(parent), m_QmlContext(qmlContext) {}

void PageRouter::NavigateTo(const QString& path) {
    emit navigateRequested(path);
}

void PageRouter::NavigateToChat(const QString& roomName, const QString& roomAvatar) {
    auto chatView = std::make_shared<epsilon::features::chat_room::view::ChatRoomView>(roomName, roomAvatar);
    auto chatPresenter = std::make_shared<epsilon::features::chat_room::presenter::ChatRoomPresenter>(chatView);

    m_CurrentChatView = chatView;
    m_CurrentChatPresenter = chatPresenter;

    m_QmlContext->setContextProperty("chatViewBackend", chatView.get());
    emit chatRoomLoaded();
}