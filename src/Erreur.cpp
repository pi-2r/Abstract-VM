#include "Erreur.hpp"

Erreur::Erreur(const ErreurType type, const std::string str) throw(): _type(type), _str(str)
{
}

Erreur::~Erreur() throw()
{
}

const char	*Erreur::what() const throw()
{
  if (this->_str.compare("") == 0)
    {
      switch (this->_type)
	{
	case SyntaxError:
	  return "Erreur de syntaxe.";

	case UnknowInstruction:
	  return "Instruction inconnue.";

	case Overflow:
	  return "Overflow d'une valeur.";

	case Underflow:
	  return "Underflow d'une valeur.";

	case InvalidPop:
	  return "Instruction pop sur une pile vide.";

	case DivByZero:
	  return "Division/Modulo par zero.";

	case NoExit:
	  return "Instruction Exit manquante.";

	case InvalidAssert:
	  return "Instruction Assert non verifiee.";

	case NoEnoughOperand:
	  return "Pas assez d'Operands pour l'operation.";

	case UnknowError:
	  return "Erreur inconnue";
	}
    }
  return (this->_str.c_str());
}

