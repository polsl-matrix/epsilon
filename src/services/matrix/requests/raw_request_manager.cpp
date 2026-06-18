#include "raw_request_manager.hpp"

#include "raw_request.hpp"
#include "iraw_request_manager.hpp"
#include "../../serialization/serialization_primitive.hpp"

#include <QNetworkAccessManager>
#include <QNetworkRequest>

namespace epsilon::services::matrix::requests {

RawRequestManager::RawRequestManager() {
    m_NetworkAccessManager = QNetworkAccessManager();
}

serialization::SerializationPrimitive RawRequestManager::Execute(RawRequest&& raw_request) const {
    QNetworkRequest request;
    request.setUrl(QUrl(raw_request.Url));
    for(const auto& [header, value] : raw_request.Headers) {
        request.SetRawHeader(header, value);
    }
    QNetworkReply *reply = mgr->post(request, data);

    // TODO: Deserialize the reply and send it back.
    // Maybe do so asynchronously - this would require API changes.

    return serialization::Null{};
}

std::string RawRequestManager::GetBaselineUrl() const {
    return m_BaselineUrl;
}

}
