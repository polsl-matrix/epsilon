#include "page_router.hpp"

#include <QObject>
#include <QString>
#include <qtmetamacros.h>

PageRouter::PageRouter(QObject *parent) : QObject(parent) {}

void PageRouter::NavigateTo(const QString &path) {
    emit navigateRequested(path);
}