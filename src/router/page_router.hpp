#pragma once

#include <QObject>
#include <QString>
#include <QQmlContext>
#include <memory>

class PageRouter : public QObject {
    Q_OBJECT

public:
    explicit PageRouter(QQmlContext* qmlContext, QObject* parent = nullptr);
    Q_INVOKABLE void NavigateTo(const QString& path);
    Q_INVOKABLE void NavigateToChat(const QString& roomName, const QString& roomAvatar);

signals:
    void navigateRequested(const QString& path);
    void chatRoomLoaded();

private:
    QQmlContext* m_QmlContext;
    std::shared_ptr<QObject> m_CurrentChatView;
    std::shared_ptr<void> m_CurrentChatPresenter;
};