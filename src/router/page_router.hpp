#pragma once

#include <QObject>
#include <QString>

namespace epsilon::router {

class PageRouter : public QObject {
    Q_OBJECT
  public:
    explicit PageRouter(QObject *parent = nullptr);

  
    void NavigateTo(const QString &path);

  signals:
    void navigateRequested(const QString &_t1);
};

}
