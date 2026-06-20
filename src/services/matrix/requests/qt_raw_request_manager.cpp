#include "qt_raw_request_manager.hpp"

#include "../../../util/qt.hpp"
#include "http_method.hpp"
#include "raw_reply.hpp"
#include "raw_request.hpp"

#include <functional>
#include <optional>
#include <stdexcept>
#include <utility>

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

    QNetworkReply *reply = PerformRequest(request, raw_request);

    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        reply->deleteLater();

        RawReply async_reply;

        if (reply->error() != QNetworkReply::NoError) {
            auto statusCodeVar =
                reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

            async_reply.StatusCode =
                statusCodeVar.isValid() ? statusCodeVar.toInt() : 0;

            const auto errorResponseBody = reply->readAll();

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

QNetworkReply *
QtRawRequestManager::PerformRequest(const QNetworkRequest &request,
                                    const RawRequest &raw_request) {
    switch (raw_request.Method) {
    case HttpMethod::GET:
        if (raw_request.Body.has_value()) {
            return m_NetworkAccessManager.get(
                request, util::qt::StdStringToQByteArray(*raw_request.Body));
        } else {
            return m_NetworkAccessManager.get(request);
        }
        break;

    case HttpMethod::POST:
        if (raw_request.Body.has_value()) {
            return m_NetworkAccessManager.post(
                request, util::qt::StdStringToQByteArray(*raw_request.Body));
        } else {
            return m_NetworkAccessManager.post(request, QByteArray());
        }
        break;

    case HttpMethod::PUT:
        if (raw_request.Body.has_value()) {
            return m_NetworkAccessManager.put(
                request, util::qt::StdStringToQByteArray(*raw_request.Body));
        } else {
            return m_NetworkAccessManager.put(request, QByteArray());
        }
        break;
    }

    throw std::runtime_error("Received an unknown HttpMethod");
}

} // namespace epsilon::services::matrix::requests::qt
