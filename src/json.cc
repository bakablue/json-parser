#include "../includes/json.hh"

// TODO Test with an empty string
namespace json
{

  Array::Array(std::ifstream& stream)
  {
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

  void parse(std::string filename)
  {
    std::ifstream stream(filename);
    char c;
    do
    {
      c = stream.get();
    } while (c != '{' && c != '[');

    if (c == '{')
    {
      Object map{stream};
      for (auto o : map)
        std::cout << o << std::endl;
    }
    else
    {
      Array map{stream};
      std::cout << map << std::endl;
    }
  };

}

