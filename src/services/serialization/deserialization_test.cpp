#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "serialization_primitive.hpp"
#include "deserialization_exception.hpp"
#include "json/json_deserialization_strategy.hpp"
#include "deserializer.hpp"
#include "deserializable.hpp"

using namespace epsilon::services::matrix::serialization;
using namespace epsilon::services::matrix::serialization::json;

struct DummyUserType {
    std::string name;
    double score;
};

struct DummyNestedType {
    std::vector<DummyUserType> users;
};

namespace epsilon::services::matrix::serialization {

template<>
::DummyUserType Deserialize<::DummyUserType>(SerializationPrimitive primitive) {
    if (!std::holds_alternative<RObject>(primitive)) {
        throw DeserializationUnexpectedPrimitiveException(Object{}, primitive);
    }
    
    const auto& wrapped_obj = std::get<RObject>(primitive);
    const Object& obj = wrapped_obj.get(); 
    ::DummyUserType result;
    
    if (obj.values.contains("name") && std::holds_alternative<String>(obj.values.at("name"))) {
        result.name = std::get<String>(obj.values.at("name")).value;
    }
    if (obj.values.contains("score") && std::holds_alternative<Number>(obj.values.at("score"))) {
        result.score = std::get<Number>(obj.values.at("score")).value;
    }
    
    return result;
}

template<>
::DummyNestedType Deserialize<::DummyNestedType>(SerializationPrimitive primitive) {
    if (!std::holds_alternative<RObject>(primitive)) {
        throw DeserializationUnexpectedPrimitiveException(Object{}, primitive);
    }
    
    const auto& wrapped_obj = std::get<RObject>(primitive);
    const Object& obj = wrapped_obj.get();
    ::DummyNestedType result;
    
    if (obj.values.contains("users")) {
        const auto& users_primitive = obj.values.at("users");
        
        if (!std::holds_alternative<RArray>(users_primitive)) {
            throw DeserializationUnexpectedPrimitiveException(Array{}, users_primitive);
        }
        
        const auto& wrapped_arr = std::get<RArray>(users_primitive);
        const Array& array_data = wrapped_arr.get();
        result.users.reserve(array_data.values.size());
        
        for (const auto& element : array_data.values) {
            result.users.push_back(Deserialize<::DummyUserType>(element));
        }
    }
    
    return result;
}

} // namespace epsilon::services::matrix::serialization


TEST(JsonDeserializationStrategyTest, DeserializesPrimitivesCorrectly) {
    JsonDeserializationStrategy strategy;

    std::string json_input = R"({
        "str": "hejo",
        "num": 42.67,
        "flag_true": true,
        "flag_false": false,
        "empty": null
    })";

    auto primitive = strategy.Deserialize(json_input);
    ASSERT_TRUE(std::holds_alternative<RObject>(primitive));
    
    const auto& obj = std::get<RObject>(primitive).get();
    
    EXPECT_EQ(std::get<String>(obj.values.at("str")).value, "hejo");
    EXPECT_DOUBLE_EQ(std::get<Number>(obj.values.at("num")).value, 42.67);
    EXPECT_TRUE(std::holds_alternative<True>(obj.values.at("flag_true")));
    EXPECT_TRUE(std::holds_alternative<False>(obj.values.at("flag_false")));
    EXPECT_TRUE(std::holds_alternative<Null>(obj.values.at("empty")));
}

TEST(JsonDeserializationStrategyTest, DeserializesNestedArrayCorrectly) {
    JsonDeserializationStrategy strategy;
    std::string json_input = "[10, \"mixed\", true]";

    auto primitive = strategy.Deserialize(json_input);
    ASSERT_TRUE(std::holds_alternative<RArray>(primitive));
    
    const auto& arr = std::get<RArray>(primitive).get();
    ASSERT_EQ(arr.values.size(), 3);
    
    EXPECT_DOUBLE_EQ(std::get<Number>(arr.values[0]).value, 10.0);
    EXPECT_EQ(std::get<String>(arr.values[1]).value, "mixed");
    EXPECT_TRUE(std::holds_alternative<True>(arr.values[2]));
}

TEST(JsonDeserializationStrategyTest, ThrowsOnMalformedJsonSyntax) {
    JsonDeserializationStrategy strategy;
    std::string malformed_json = "{ name: \"missing_quotes_on_key\" ";

    EXPECT_THROW({
        try {
            strategy.Deserialize(malformed_json);
        } catch(const DeserializationUnrecognizedFormatException& e) {
            EXPECT_EQ(e.ExpectedFormat(), "JSON");
            throw; 
        }
    }, DeserializationUnrecognizedFormatException);
}

TEST(DeserializerTest, StaticConstructAndPipelineIntegration) {
    auto deserializer = Deserializer::Construct<JsonDeserializationStrategy>();
    
    std::string json_payload = "{\"name\":\"Alice\",\"score\":98.5}";
    
    DummyUserType user = deserializer.Deserialize<DummyUserType>(json_payload);
    
    EXPECT_EQ(user.name, "Alice");
    EXPECT_DOUBLE_EQ(user.score, 98.5);
}

TEST(DeserializerTest, DeserializesNestedTypeStructure) {
    auto deserializer = Deserializer::Construct<JsonDeserializationStrategy>();
    
    std::string complex_json = R"({
        "users": [
            {"name": "Bob", "score": 85.0},
            {"name": "Charlie", "score": 92.3}
        ]
    })";
    
    DummyNestedType nested_data = deserializer.Deserialize<DummyNestedType>(complex_json);
    
    ASSERT_EQ(nested_data.users.size(), 2);
    
    EXPECT_EQ(nested_data.users[0].name, "Bob");
    EXPECT_DOUBLE_EQ(nested_data.users[0].score, 85.0);
    
    EXPECT_EQ(nested_data.users[1].name, "Charlie");
    EXPECT_DOUBLE_EQ(nested_data.users[1].score, 92.3);
}