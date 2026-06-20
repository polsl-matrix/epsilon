#include "qt_raw_request_manager.hpp"

#include "../../../util/qt.hpp"
#include "../../serialization/serialization_primitive.hpp"
#include "http_method.hpp"
#include "iraw_request_manager.hpp"
#include "raw_request.hpp"

#include <format>
#include <iostream>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>

namespace epsilon::services::matrix::requests::qt {

QtRawRequestManager::QtRawRequestManager(QObject *parent) : QObject(parent) {}

void QtRawRequestManager::Execute(RawRequest &&raw_request,
                                  std::function<void(RawReply)> callback) {
    QNetworkRequest request;
    request.setUrl(QUrl(QString::fromStdString(raw_request.Url)));
    for (const auto &[header, value] : raw_request.Headers) {
        request.setRawHeader(util::qt::StdStringToQByteArray(header),
                             util::qt::StdStringToQByteArray(value));
    }

    QNetworkReply *reply;

    switch (raw_request.Method) {
    case HttpMethod::GET:
        if (raw_request.Body.has_value()) {
            reply = m_NetworkAccessManager.get(
                request, util::qt::StdStringToQByteArray(*raw_request.Body));
        } else {
            reply = m_NetworkAccessManager.get(request);
        }
        break;

    case HttpMethod::POST:
        if (raw_request.Body.has_value()) {
            reply = m_NetworkAccessManager.post(
                request, util::qt::StdStringToQByteArray(*raw_request.Body));
        } else {
            reply = m_NetworkAccessManager.post(request, QByteArray());
        }
        break;

    case HttpMethod::PUT:
        if (raw_request.Body.has_value()) {
            reply = m_NetworkAccessManager.put(
                request, util::qt::StdStringToQByteArray(*raw_request.Body));
        } else {
            reply = m_NetworkAccessManager.put(request, QByteArray());
        }
        break;
    }

    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        reply->deleteLater();

        RawReply async_reply;

        if (reply->error() != QNetworkReply::NoError) {
            QVariant statusCodeVar =
                reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

            async_reply.StatusCode =
                statusCodeVar.isValid() ? statusCodeVar.toInt() : 0;

            QByteArray errorResponseBody = reply->readAll();

            if (!errorResponseBody.isEmpty()) {
                async_reply.Body = errorResponseBody.toStdString();
            } else {
                async_reply.Body = std::nullopt;
            }
        } else {
            async_reply.StatusCode =
                reply->attribute(QNetworkRequest::HttpStatusCodeAttribute)
                    .toInt();
            async_reply.Body = reply->readAll().toStdString();

            if (async_reply.Body.value().empty()) {
                async_reply.Body = std::nullopt;
            }
        }

        if (callback) {
            callback(std::move(async_reply));
        }
    });
}

} // namespace epsilon::services::matrix::requests::qt
