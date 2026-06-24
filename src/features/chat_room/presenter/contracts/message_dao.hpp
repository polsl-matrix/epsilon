#pragma once

#include <string>

namespace epsilon::features::chat_room {

struct MessageDao {
    std::string Author;
    std::string Content;
    bool IsMe;
};

}
