#pragma once

#include <QObject>
#include <QString>
#include <QQmlContext>

namespace epsilon::services::router {

class PageRouter : public QObject {
    Q_OBJECT

    QQmlContext* m_QmlContext;
  public:
    explicit PageRouter(QQmlContext* qml_context, QObject *parent = nullptr);

    void Display(const QString &path, const QString &view_qt_name, QObject* view);
    void Bind(const QString &view_qt_name, QObject* view);

  signals:
    void navigateRequested(const QString &_t1);
};

}
