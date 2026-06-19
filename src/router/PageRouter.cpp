#include "PageRouter.hpp"

PageRouter::PageRouter(QObject *parent) : QObject(parent) {}

void PageRouter::navigateTo(const QString &path) {
    emit navigateRequested(path);
}