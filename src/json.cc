#include "../includes/json.hh"

// TODO Test with an empty string
namespace json
{
      void Object::parse(std::istream& stream)
      {
        char c;
        if (stream.get() == '{')
        {
          while ((c = stream.peek()) == '}')
          {
            if (c == ' ')
              c << stream;
            else if (c == '"')
            {
              
            }
          }
        }
        else
        {
          // error
        }
      }

      void Map::parse(std::istream& stream)
      {
        char c;
        String s;

        // Parse String
        do {
          c << stream;
        } while (c == ' ' || c == '\n');

        if (c == "")
        {
          if (!s.parse(stream))
            ; // Error
        }

        else
          ;// Error

        // Parse JsonValue
        while ((c = stream.get()) != ',' || c != '}')
        {
          if (c == '"')
          {
            String s;
            s.parse(stream);
          }
          else if (isdigit(c))
          {
            Integer i;
            i.parse(stream);
          }
          else if (c == '{')
          {
            Object o;
            o.parse(stream);
          }
          else if (c == '[')
          {
            Array a;
            a.parse(stream);
          }
        }
      }
}
