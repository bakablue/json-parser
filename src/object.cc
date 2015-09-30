#include "../includes/json.hh"

namespace json
{

  Object::Object(std::ifstream& stream)
  {
    std::cout << "begin Object " << stream.tellg() << std::endl;
    char c;
    do
    {
      c = stream.peek();

      if (c != ' ' && c != '\n')
      {
        std::cout << c<< std::endl;
        elts_.push_back(Map(stream));
      }

      c = stream.get();

    } while (c != '}');
    print(std::cout);
    std::cout << std::endl;
    std::cout << "end Object " << stream.tellg() << std::endl;
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

  const Map& Object::operator[](size_t pos) const
  {
    return elts_[pos];
  }

  Map& Object::operator[](size_t pos)
  {
    return elts_[pos];
  }

  iterator Object::begin()
  {
    return elts_.begin();
  }
  citerator Object::begin() const
  {
    return elts_.begin();
  }
  iterator  Object::end()
  {
    return elts_.end();
  }
  citerator Object::end() const
  {
    return elts_.end();
  }

  /*Object& Object::operator=(const Object& other)
    {
    }
    Object& Object::operator=(Object&&      other)
    {
    }
    Object& Object::operator=(std::initializer_list<Map> ilist)
    {
    }
    */

}
