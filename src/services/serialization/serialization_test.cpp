#include "iserializable.hpp"
#include "serialization_primitive.hpp"
#include "serializer.hpp"
#include "json/json_serialization_strategy.hpp"

#include <gtest/gtest.h>

#include <format>
#include <string>
#include <unordered_map>
#include <utility>
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
    const JsonSerializationStrategy strategy;
    const SerializationPrimitive primitive = String{"hello"};

    EXPECT_EQ(strategy.Serialize(primitive), "\"hello\"");
}

TEST(JsonSerializationStrategyTest, SerializesNumberCorrectly) {
    const JsonSerializationStrategy strategy;
    const SerializationPrimitive primitive = Number{42.5};

    EXPECT_EQ(strategy.Serialize(primitive), std::to_string(42.5));
}

TEST(JsonSerializationStrategyTest, SerializesBooleansAndNullCorrectly) {
    const JsonSerializationStrategy strategy;

    EXPECT_EQ(strategy.Serialize(True{}), "true");
    EXPECT_EQ(strategy.Serialize(False{}), "false");
    EXPECT_EQ(strategy.Serialize(Null{}), "null");
}

TEST(JsonSerializationStrategyTest, SerializesEmptyArrayAndObject) {
    const JsonSerializationStrategy strategy;

    const SerializationPrimitive empty_array =
        Array{std::vector<SerializationPrimitive>{}};
    EXPECT_EQ(strategy.Serialize(empty_array), "[]");

    const SerializationPrimitive empty_object =
        Object{std::unordered_map<std::string, SerializationPrimitive>{}};
    EXPECT_EQ(strategy.Serialize(empty_object), "{}");
}

TEST(JsonSerializationStrategyTest,
     SerializesPopulatedArrayWithoutTrailingComma) {
    const JsonSerializationStrategy strategy;

    std::vector<SerializationPrimitive> elements;
    elements.push_back(String{"first"});
    elements.push_back(Number{2.0}); // NOLINT(readability-magic-numbers)
    elements.push_back(True{});

    const SerializationPrimitive array_primitive = Array{elements};

    const std::string expected =
        std::format("[\"first\",{},true]",
                    std::to_string(2.0)); // NOLINT(readability-magic-numbers)
    EXPECT_EQ(strategy.Serialize(array_primitive), expected);
}

TEST(JsonSerializationStrategyTest,
     SerializesPopulatedObjectWithoutTrailingComma) {
    const JsonSerializationStrategy strategy;

    std::unordered_map<std::string, SerializationPrimitive> map_elements;
    map_elements["key1"] = String{"val1"};

    const SerializationPrimitive object_primitive = Object{map_elements};

    EXPECT_EQ(strategy.Serialize(object_primitive), "{\"key1\":\"val1\"}");
}

TEST(SerializerTest, CompleteSerializationPipeline) {
    const auto serializer = Serializer::Construct<JsonSerializationStrategy>();

    const auto val1 = 6.0;
    const auto val2 = 7.0;

    const std::vector<SerializationPrimitive> array_vals = {Number{val1},
                                                            Number{val2}};

    std::unordered_map<std::string, SerializationPrimitive> obj_vals;
    obj_vals["list"] =
        Array{array_vals}; // Recursive serialization (array is in an object)

    const MockSerializable serializable_obj(Object{obj_vals});

    const auto expected_json = std::format(
        "{{\"list\":[{},{}]}}", std::to_string(val1), std::to_string(val2));

    EXPECT_EQ(serializer.Serialize(serializable_obj), expected_json);
}

TEST(SerializerTest, TemplatedConstructorForwarding) {
    auto serializer = Serializer::Construct<JsonSerializationStrategy>();

    const MockSerializable string_box(String{"test"});
    EXPECT_EQ(serializer.Serialize(string_box), "\"test\"");
}
