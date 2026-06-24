#include "message.hpp"

#include "user.hpp"

#include <string>
#include <utility>

namespace epsilon::model {

Message::Message(User author, std::string content)
    : m_Author(std::move(author)), m_Content(std::move(content)) {}

User Message::Author() const { return m_Author; }

std::string Message::Content() const { return m_Content; }

} // namespace epsilon::model