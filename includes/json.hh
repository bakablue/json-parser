#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <boost/variant.hpp>

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
  // Primitive type
  // XXX Note: it can begin by "[]"

  class JsonValue
  {  
    public:
      virtual void print(std::ostream& os) const { os << "Undefined"; };
  };

  class Map
  {
    public:
      Map(std::ifstream& stream);
      void print(std::ostream& os) const;
    private:
      // key + obj
      void parse_key(std::ifstream& stream);
      void parse_string(std::ifstream& stream, std::string& value);
      void parse_number(std::ifstream& stream, double& d);
    private:
      std::string key_;
      std::shared_ptr<JsonValue> value_;
      enum MapState { KEY, VALUE } state_;
  };

  class Object : public JsonValue
  {
    public:
      Object(std::ifstream& stream);
      void print(std::ostream& os) const;
    private:
      std::vector<Map> elts_;
  };

  class Array : public JsonValue
  {
    public:
      Array(std::ifstream& stream);
      void print(std::ostream& os) const;
    private:
      std::vector<Object> objects_;
  };


  typedef boost::variant<std::string, double> ptype;

  class PrimitiveValue : public JsonValue
  {

    public:
      PrimitiveValue(double      value);
      PrimitiveValue(std::string value);

      ptype getValue() const { return value_; };
      void print(std::ostream& os) const;
    private:
      ptype value_;
  };

  std::ostream& operator<<(std::ostream& os, const JsonValue& pvalue);
};
