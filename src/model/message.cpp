#include "message.hpp"

#include "user.hpp"

#include <chrono>
#include <string>
#include <utility>

namespace epsilon::model {

Message::Message(User author, std::string content, std::chrono::time_point<std::chrono::system_clock> timestamp)
    : m_Author(std::move(author)), m_Content(std::move(content)), m_Timestamp(timestamp) {}

User Message::Author() const { return m_Author; }

std::string Message::Content() const { return m_Content; }

std::chrono::time_point<std::chrono::system_clock> Message::Timestamp() const { return m_Timestamp; }

} // namespace epsilon::model