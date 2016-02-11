#include <fstream>
#include <iostream>
#include "avm.hpp"
#include "Erreur.hpp"

bool	start_avm(const char *path)
{
  std::fstream	file;

  file.open(path, std::ifstream::in);
  if (file.is_open() == false)
    return false;
  core_avm(file);
  file.close();
  return true;
}

void	core_avm(std::istream &stream)
{
  avm	machine(stream);

  machine.read_stream();
  machine.tokenise();
  machine.execute();
}
