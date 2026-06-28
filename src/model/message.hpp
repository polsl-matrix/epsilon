#pragma once

#include "user.hpp"

#include <chrono>
#include <string>

namespace epsilon::model {

class Message {
    User m_Author;
    std::string m_Content;
    std::chrono::time_point<std::chrono::system_clock> m_Timestamp;

public:
    Message(User author, std::string content, std::chrono::time_point<std::chrono::system_clock> timestamp);

    User Author() const;
    std::string Content() const;
    std::chrono::time_point<std::chrono::system_clock> Timestamp() const;
};

}