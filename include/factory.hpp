#ifndef FACTORY_HH_
#define FACTORY_HH_

#include "Operand.hpp"

namespace	factory
{
  IOperand	*new_operand(const S32 nb, const eOperandType type);
  IOperand	*new_operand(const double nb, const eOperandType type);
};

#endif
