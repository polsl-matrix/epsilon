#pragma once

#include "raw_reply.hpp"
#include "raw_request.hpp"
#include "iraw_request_manager.hpp"

#include <functional>
#include <string>

#include <QObject>
#include <QNetworkAccessManager>

namespace epsilon::services::matrix::requests::qt {

class QtRawRequestManager : public QObject, public IRawRequestManager {
    Q_OBJECT

    QNetworkAccessManager m_NetworkAccessManager;

public:
    QtRawRequestManager(QObject* parent = nullptr);

    virtual void Execute(RawRequest&& request, std::function<void(RawReply)> callback) override;
};

}
