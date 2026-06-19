#include "qt.hpp"

#include <string>

#include <QByteArray>

namespace epsilon::util::qt {

QByteArray StdStringToQByteArray(const std::string& string) {
    return QByteArray(string.c_str(), string.length());
}

} // namespace epsilon::util::qt
