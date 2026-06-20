#include "json_deserialization_strategy.hpp"

#include "../deserialization_exception.hpp"
#include "../serialization_primitive.hpp"

#include <string>

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

namespace epsilon::services::matrix::serialization::json {

SerializationPrimitive
JsonDeserializationStrategy::Deserialize(const std::string &serialized) const {
    auto jsonData = QByteArray::fromStdString(serialized);

    QJsonParseError parseError;
    auto jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        throw DeserializationUnrecognizedFormatException("JSON");
    }

    if (jsonDoc.isObject()) {
        return ConvertJsonValue(jsonDoc.object());
    }

    if (jsonDoc.isArray()) {
        return ConvertJsonValue(jsonDoc.array());
    }

    if (jsonDoc.isNull()) {
        return Null{};
    }

    throw DeserializationUnrecognizedFormatException("JSON");
}

SerializationPrimitive JsonDeserializationStrategy::ConvertJsonValue(
    const QJsonValue &jsonValue) const {
    switch (jsonValue.type()) {
    case QJsonValue::Null:
        return Null{};

    case QJsonValue::Bool:
        if (jsonValue.toBool()) {
            return True{};
        } else {
            return False{};
        }

    case QJsonValue::Double:
        return Number{jsonValue.toDouble()};

    case QJsonValue::String:
        return String{jsonValue.toString().toStdString()};

    case QJsonValue::Array: {
        auto jsonArray = jsonValue.toArray();
        Array customArray;
        customArray.values.reserve(jsonArray.size());

        for (const auto &element : jsonArray) {
            customArray.values.push_back(ConvertJsonValue(element));
        }
        return customArray;
    }

    case QJsonValue::Object: {
        auto jsonObject = jsonValue.toObject();
        Object customObject;

        for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
            auto key = it.key().toStdString();
            customObject.values[key] = ConvertJsonValue(it.value());
        }
        return customObject;
    }

    case QJsonValue::Undefined:
    default:
        throw DeserializationUnrecognizedFormatException("JSON");
    }
}

} // namespace epsilon::services::matrix::serialization::json
