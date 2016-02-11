#include <iostream>
#include <cstdlib>
#include "avm.hpp"
#include "Erreur.hpp"

//main avec gestion des exceptions
int	main(int argc, char *argv[])
{
  try
    {
		if (argc == 1)
		{
		  std::cout << "Utilisation de std::cin" << std::endl;
		  core_avm(std::cin);
		}
		else
		{
		  std::cout << "Lecture de fichier(s) :" << std::endl;
		  for (int i = 1; i < argc; i++)
			{
			  std::cout << "\tOuverture de \"" << argv[i] << "\""<< std::endl << std::endl;
			  if (start_avm(argv[i]) == false)
			std::cerr << "\t\tEchec à l'ouverture du fichier !" << std::endl;
			}
		}
    }
	catch ( const std::exception &e)
    {
      std::cerr <<  "Exception : " << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
