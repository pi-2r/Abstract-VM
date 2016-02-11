#include <iostream>
#include "Operand.hpp"
#include "avm.hpp"

static	void	print_code(token &token)
{
  switch (token.code)
    {
    case Push:
      std::cout << "Push";
      break;

    case Pop:
      std::cout<< "Pop";
      break;

    case Dump:
      std::cout<< "Dump";
	break;

    case Assert:
      std::cout<< "Assert";
      break;

    case Add:
      std::cout<< "Add";
	break;

    case Sub:
      std::cout<< "Sub";
      break;

    case Mul:
      std::cout<< "Mul";
	break;

    case Div:
      std::cout<< "Div";
      break;

    case Mod:
      std::cout<< "Mod";
      break;

    case Print:
      std::cout<< "Print";
      break;

    case Exit:
      std::cout<< "Exit";
      break;

    default:
      std::cout << "Inconnue";
    }
}

static	void	print_type(token &token)
{
  std::cout << "   ";
  switch (token.type)
    {
    case Int8:
      std::cout << "Int8 = " << (S32)((S8)(token.valueI));
      break;

    case Int16:
      std::cout << "Int16 = "<< (S16)(token.valueI);
      break;

    case Int32:
      std::cout << "Int32 = "<< (S32)(token.valueI);
      break;

    case Float:
      std::cout << "Float = "<< (float)(token.valueD);
      break;

    case Double:
      std::cout << "Double = "<< (double)(token.valueD);
      break;
    }
}

void	token::dump()
{
  print_code(*this);
  if (this->code == Assert || this->code == Push)
    print_type(*this);
  std::cout << std::endl;
}

void    avm::dump_all_token(void)
{
  int   i = 0;
  int   size = this->list_token.size();

  std::cout << std::endl << std::endl;
  while (i < size)
    {
      list_token[i]->dump();
      i++;
    }
}
