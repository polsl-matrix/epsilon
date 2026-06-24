#pragma once

#include "user.hpp"

#include <string>

namespace epsilon::model {

class Message {
    User m_Author;
    std::string m_Content;

public:
    Message(User author, std::string content);

    User Author() const;
    std::string Content() const;
};

}