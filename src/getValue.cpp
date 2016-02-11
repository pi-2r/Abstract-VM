#include <sstream>
#include "type.hpp"

// Renvoie un int
S32                     getValueI(const std::string &str)
{
  S32                   val;
  std::istringstream    buffer(std::istringstream::in);

  buffer.str(str);
  buffer >> val;
  return val;
}

double                  getValueD(const std::string &str)
{
  double                val;
  std::istringstream    buffer(std::istringstream::in);

  buffer.str(str);
  buffer >> val;
  return val;
}
