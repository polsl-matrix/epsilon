#include "room.hpp"

#include "../services/matrix/requests/authenticated_request_manager.hpp"

#include "message.hpp"
#include "user.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace epsilon::model {

Room::Room(std::shared_ptr<RequestManager> request_manager, std::string id)
    : m_RequestManager(std::move(request_manager)), m_Id(std::move(id)) {
    m_Messages = {
        { User(m_RequestManager, "joker"), "why so queerious?" },
        { User(m_RequestManager, "guy"), "wtf man" },
        { User(m_RequestManager, "guy"),
          "why are you terrorizing gotham city?" },
        { User(m_RequestManager, "joker"), "gotham deez nuts" },
        { User(m_RequestManager, "joker"), "hee hee hee" },
        { User(m_RequestManager, "user"), "lol" },
    };
}

std::string Room::Id() const { return m_Id; }

std::string Room::Name() const {
    std::string name = "";

    for(size_t i = 1; i < 9 && i < m_Id.size(); i++) {
        name += m_Id[i];
    }

    return name;
}

std::vector<Message> Room::MessageList() const { return m_Messages; }

void Room::SendMessage(std::string content) {
    m_Messages.push_back(
        { User(m_RequestManager, "joker"), std::move(content) });
}

} // namespace epsilon::model