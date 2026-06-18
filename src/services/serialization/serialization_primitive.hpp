#pragma once

#include "../../util/recursive_wrapper/recursive_wrapper.hpp"

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace epsilon::services::matrix::serialization {

using epsilon::util::RecursiveWrapper;

struct String { std::string value; };
struct Number { double value; };
struct True   { };
struct False  { };
struct Null   { };

struct Array;
struct Object;

using SerializationPrimitive = std::variant<String, Number, True, False, Null, RecursiveWrapper<Array>, RecursiveWrapper<Object>>;

struct Array {
  std::vector<SerializationPrimitive> values;
};

struct Object {
  std::unordered_map<std::string, SerializationPrimitive> values;
};

}