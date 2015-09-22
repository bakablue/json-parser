#pragma once

#include <string>
#include <iostream>

// {}
// { [] }
// { "toto" : "tata" }

// Array, Map, Object
// String
// Null
// Boolean
// Array
// Number
// Object


namespace json
{
  typedef std::tuple<std::string, JsonValue> Map;

  class JsonValue
  {
    public:
      virtual void parse(std::istream& stream) = 0;
  };

  class Object : JsonValue // {}
  {
    public:
      void parse(std::istream& stream);
    private:
      std::vector<Map> data_;
  };
  class Array : JsonValue // []
  {
    public:
      void parse(std::istream& stream);
    private:
      std::vector<Object> data_;
  };

  // Primitive types
  class PrimitiveType {};

  class String : PrimitiveType
  {
  };

  class Boolean : PrimitiveType
  {
  };

  class NullValue {};

  class Integer : PrimitiveType
  {
  };

};
