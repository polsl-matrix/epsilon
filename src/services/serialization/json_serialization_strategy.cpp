#include "json_serialization_strategy.hpp"

#include "serialization_primitive.hpp"

#include <format>
#include <string>
#include <variant>

// Helper struct for the visitor
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

namespace epsilon::services::matrix::serialization {

std::string JsonSerializationStrategy::Serialize(SerializationPrimitive primitive) const {
    return std::visit(overloaded {
        [] (String value) { return std::format("\"{}\"", value.value); },
        [] (Number value) { return std::to_string(value.value); },
        [] (True) { return std::string("true"); },
        [] (False) { return std::string("false"); },
        [] (Null) { return std::string("null"); },
        [this] (Array array) {
            std::string result = "[";

            for(size_t i = 0; i < array.values.size(); i++) {
                result += this->Serialize(array.values[i]);

                if(i < array.values.size() - 1) {
                    result += ",";
                }
            }

            result += "]";

            return result;
        },
        [this] (Object object) {
            std::string result = "{";

            bool first = true;

            for (const auto& [key, value] : object.values) {
                if (!first) {
                    result += ",";
                }
                first = false;

                result += std::format("\"{}\":{}", key, this->Serialize(value));
            }

            result += "}";

            return result;
        } }, primitive
    );
}

}
