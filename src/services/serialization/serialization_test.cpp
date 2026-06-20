#include "iserializable.hpp"
#include "serialization_primitive.hpp"
#include "serializer.hpp"
#include "json/json_serialization_strategy.hpp"

#include <gtest/gtest.h>

#include <format>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace epsilon::services::matrix::serialization;
using namespace epsilon::services::matrix::serialization::json;

class MockSerializable : public ISerializable {
    SerializationPrimitive m_primitive;

  public:
    MockSerializable(SerializationPrimitive primitive)
        : m_primitive(std::move(primitive)) {}

  protected:
    SerializationPrimitive GetPrimitiveRepresentation() const override {
        return m_primitive;
    }
};

TEST(JsonSerializationStrategyTest, SerializesStringCorrectly) {
    JsonSerializationStrategy strategy;
    SerializationPrimitive primitive = String{"hello"};

    EXPECT_EQ(strategy.Serialize(primitive), "\"hello\"");
}

TEST(JsonSerializationStrategyTest, SerializesNumberCorrectly) {
    JsonSerializationStrategy strategy;
    SerializationPrimitive primitive = Number{42.5};

    EXPECT_EQ(strategy.Serialize(primitive), std::to_string(42.5));
}

TEST(JsonSerializationStrategyTest, SerializesBooleansAndNullCorrectly) {
    JsonSerializationStrategy strategy;

    EXPECT_EQ(strategy.Serialize(True{}), "true");
    EXPECT_EQ(strategy.Serialize(False{}), "false");
    EXPECT_EQ(strategy.Serialize(Null{}), "null");
}

TEST(JsonSerializationStrategyTest, SerializesEmptyArrayAndObject) {
    JsonSerializationStrategy strategy;

    SerializationPrimitive empty_array =
        Array{std::vector<SerializationPrimitive>{}};
    EXPECT_EQ(strategy.Serialize(empty_array), "[]");

    SerializationPrimitive empty_object =
        Object{std::unordered_map<std::string, SerializationPrimitive>{}};
    EXPECT_EQ(strategy.Serialize(empty_object), "{}");
}

TEST(JsonSerializationStrategyTest,
     SerializesPopulatedArrayWithoutTrailingComma) {
    JsonSerializationStrategy strategy;

    std::vector<SerializationPrimitive> elements;
    elements.push_back(String{"first"});
    elements.push_back(Number{2.0});
    elements.push_back(True{});

    SerializationPrimitive array_primitive = Array{elements};

    std::string expected =
        std::format("[\"first\",{},true]", std::to_string(2.0));
    EXPECT_EQ(strategy.Serialize(array_primitive), expected);
}

TEST(JsonSerializationStrategyTest,
     SerializesPopulatedObjectWithoutTrailingComma) {
    JsonSerializationStrategy strategy;

    std::unordered_map<std::string, SerializationPrimitive> map_elements;
    map_elements["key1"] = String{"val1"};

    SerializationPrimitive object_primitive = Object{map_elements};

    EXPECT_EQ(strategy.Serialize(object_primitive), "{\"key1\":\"val1\"}");
}

TEST(SerializerTest, CompleteSerializationPipeline) {
    auto strategy = std::make_unique<JsonSerializationStrategy>();
    Serializer serializer(std::move(strategy));

    std::vector<SerializationPrimitive> array_vals = {Number{1.0}, Number{2.0}};

    std::unordered_map<std::string, SerializationPrimitive> obj_vals;
    obj_vals["list"] =
        Array{array_vals}; // Recursive serialization (array is in an object)

    MockSerializable serializable_obj(Object{obj_vals});

    std::string expected_json = std::format(
        "{{\"list\":[{},{}]}}", std::to_string(1.0), std::to_string(2.0));

    EXPECT_EQ(serializer.Serialize(serializable_obj), expected_json);
}

TEST(SerializerTest, TemplatedConstructorForwarding) {
    auto serializer = Serializer::Construct<JsonSerializationStrategy>();

    MockSerializable string_box(String{"test"});
    EXPECT_EQ(serializer.Serialize(string_box), "\"test\"");
}
