#include "json_deserialization_strategy.hpp"

#include "../deserialization_exception.hpp"
#include "../serialization_primitive.hpp"

#include <string>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

namespace epsilon::services::matrix::serialization::json {

SerializationPrimitive JsonDeserializationStrategy::Deserialize(const std::string& serialized) const {
    QByteArray jsonData = QByteArray::fromStdString(serialized);

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        throw DeserializationUnrecognizedFormatException("JSON");
    }
    
    if (jsonDoc.isObject()) {
        return ConvertJsonValue(jsonDoc.object());
    } else if (jsonDoc.isArray()) {
        return ConvertJsonValue(jsonDoc.array());
    } else if (jsonDoc.isNull()) {
        return Null{};
    }
    
    throw DeserializationUnrecognizedFormatException("JSON");
}

SerializationPrimitive JsonDeserializationStrategy::ConvertJsonValue(const QJsonValue& jsonValue) const {
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
            return Number{ jsonValue.toDouble() };
            
        case QJsonValue::String:
            return String{ jsonValue.toString().toStdString() };
            
        case QJsonValue::Array: {
            QJsonArray jsonArray = jsonValue.toArray();
            Array customArray;
            customArray.values.reserve(jsonArray.size());
            
            for (const QJsonValue& element : jsonArray) {
                customArray.values.push_back(ConvertJsonValue(element));
            }
            return customArray; 
        }
            
        case QJsonValue::Object: {
            QJsonObject jsonObject = jsonValue.toObject();
            Object customObject;
            
            for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
                std::string key = it.key().toStdString();
                customObject.values[key] = ConvertJsonValue(it.value());
            }
            return customObject;
        }
        
        case QJsonValue::Undefined:
        default:
            throw DeserializationUnrecognizedFormatException("JSON");
    }
}

}
