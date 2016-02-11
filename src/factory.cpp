#include <iostream>
#include "Erreur.hpp"
#include "Operand.hpp"
#include "factory.hpp"

// Les erreurs de type UnknowError ne devraient jamais arriver normalement
IOperand		*factory::new_operand(const S32 nb, const eOperandType type)
{
  switch (type)
    {
    case Int8:
      return new Operand<S8>((S8)nb);

    case Int16:
      return new Operand<S16>((S16)nb);

    case Int32:
      return new Operand<S32>((S32)nb);

    default:
      throw Erreur(UnknowError, "Token invalide ou autre chose coté Operand");
      return NULL;
    }
}

IOperand		*factory::new_operand(const double nb, const eOperandType type)
{
  switch (type)
    {
    case Float:
      return new Operand<float>((float)nb);

    case Double:
      return new Operand<double>((double)nb);

    default:
      throw Erreur(UnknowError, "Token invalide ou autre chose coté Operand");
      return NULL;
    }
}

