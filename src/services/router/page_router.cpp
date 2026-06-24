#include "page_router.hpp"

#include <QObject>
#include <QQmlContext>
#include <QString>
#include <qtmetamacros.h>

namespace epsilon::services::router {

PageRouter::PageRouter(QQmlContext *qml_context, QObject *parent)
    : QObject(parent), m_QmlContext(qml_context) {}

void PageRouter::Display(const QString &path, const QString &view_qt_name,
                         QObject *view) {
    Bind(view_qt_name, view);

    emit navigateRequested(path);
}

void PageRouter::Bind(const QString &view_qt_name,
                         QObject *view) {
    m_QmlContext->setContextProperty(view_qt_name, view);
}

} // namespace epsilon::services::router
