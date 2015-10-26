#include "../includes/json.hh"
#include <iostream>
#include <fstream>

int main(void)
{
  json::parse("tests/simple.json");
  return 0;
}
