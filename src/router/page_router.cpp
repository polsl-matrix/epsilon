#include "page_router.hpp"

#include <QObject>
#include <QString>
#include <qtmetamacros.h>

namespace epsilon::router {

PageRouter::PageRouter(QObject *parent) : QObject(parent) {}

void PageRouter::NavigateTo(const QString &path) {
    emit navigateRequested(path);
}

}
