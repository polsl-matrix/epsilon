#pragma once

#include "raw_request.hpp"
#include "iraw_request_manager.hpp"
#include "../../serialization/serialization_primitive.hpp"

#include <string>

#include <QNetworkAccessManager>

namespace epsilon::services::matrix::requests {

class RawRequestManager : public IRawRequestManager {
    QNetworkAccessManager m_NetworkAccessManager;

public:
    RawRequestManager();

    virtual serialization::SerializationPrimitive Execute(RawRequest&& request) const override;
};

}
