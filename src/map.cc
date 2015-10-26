#include "../includes/json.hh"

namespace json
{
  Map::Map(std::ifstream& stream)
    : key_("")
    , state_(KEY)
  {
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
        value_ = std::make_shared<Object>(Object(stream));

      else if (c == '[')
        value_ = std::make_shared<Array>(Array(stream));

      else if (c == ':')
        state_ = VALUE;

      // object
      // map
    } while (!stream.eof());
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

  std::ostream& operator<<(std::ostream& os, const Map& map)
  {
    map.print(os);
    return os;
  }
}
