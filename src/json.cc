#include "../includes/json.hh"

// TODO Test with an empty string
namespace json
{
  Map::Map(std::ifstream& stream)
    : key_("")
    , state_(KEY)
  {
    //std::cout << "begin Map" << stream.tellg() << std::endl;
    do {
      char c = stream.peek();

      if (c == ',' || c == '}')
        break;

      stream.get();

      if (c == '"')
      {
        if (state_ == KEY)
          parse_string(stream, key_);
        else
        {
          std::string str;
          parse_string(stream, str);
          value_ = std::make_shared<PrimitiveValue>(PrimitiveValue(str));
        }
      }

      else if (std::isdigit(c))  // And state == VALUE or else -> error
      {
        stream.unget();
        double i;
        parse_number(stream, i);
        value_ = std::make_shared<PrimitiveValue>(PrimitiveValue(i));
      }
      else if (c == '-')
      {
        double i;
        parse_number(stream, i);
        value_ = std::make_shared<PrimitiveValue>(PrimitiveValue(-1 * i));
      }
      else if (c == '{')
      {
        //std::cout << "found object " << stream.tellg() << std::endl;
        value_ = std::make_shared<Object>(Object(stream));
      }
      else if (c == '[')
      {
        //std::cout << "found array " << stream.tellg() << std::endl;
        value_ = std::make_shared<Array>(Array(stream));
      }

      else if (c == ':')
        state_ = VALUE;
      // object
      // map
    } while (!stream.eof());
    //std::cout << "end Map"  << stream.tellg()<< std::endl;
  }

  void Map::parse_key(std::ifstream& stream)
  {
    parse_string(stream, key_);
  }

  void Map::parse_string(std::ifstream& stream, std::string& value)
  {
    char c;
    while ((c = stream.get()) != '"')
    {
      value += c;
    }
  }

  void Map::parse_number(std::ifstream& stream, double& value)
  {
    std::string number_str;
    char c;

    do {
      c = stream.get();
      number_str += c;
    } while (std::isdigit(c) || c == '.');

    stream.unget();
    value = std::atof(number_str.c_str());
  }

  void Map::print(std::ostream& os) const
  {
    os << key_ <<  " : " << *value_;
  }

  Object::Object(std::ifstream& stream)
  {
    //std::cout << "begin Object" << stream.tellg() << std::endl;
    char c;
    do
    {
      c = stream.peek();

      if (c != ' ' || c != '\n')
        elts_.push_back(Map(stream));

      c = stream.get();

    } while (c != '}');
    //std::cout << "end Object" << stream.tellg() << std::endl;
  }

  void Object::print(std::ostream& os) const
  {
    bool first = true;

    os << "{ ";

    for (auto m : elts_)
    {
      if (first)
        first = false;
      else
        os << ", ";
      m.print(os);
    }

    os << " }";
  }

  Array::Array(std::ifstream& stream)
  {
    //std::cout << "begin Array" << stream.tellg() << std::endl;
    char c;
    do
    {
      c = stream.peek();

      if (c == '{')
      {
        stream.get();
        objects_.push_back(Object(stream));
      }

      c = stream.get();

    } while (c != ']');
    //std::cout << "end Array" << stream.tellg() << std::endl;
  }

  void Array::print(std::ostream& os) const
  {
    bool first = true;

    os << "[ ";
    for (auto o : objects_)
    {
      if (first)
        first = false;
      else
        os << ", ";
      os << o;

    }
    os << " ]";
  }

  PrimitiveValue::PrimitiveValue(double value)
    : value_(value)
  {
  }

  PrimitiveValue::PrimitiveValue(std::string value)
    : value_(value)
  {
  }

  void PrimitiveValue::print(std::ostream& os) const
  {
    os << value_;
  }


  std::ostream& operator<<(std::ostream& os, const JsonValue& pvalue)
  {
    pvalue.print(os);
    return os;
  }
}
