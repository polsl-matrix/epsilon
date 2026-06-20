#include "PageRouter.hpp"

PageRouter::PageRouter(QObject *parent) : QObject(parent) {}

void PageRouter::NavigateTo(const QString &path) {
    emit navigateRequested(path);
}