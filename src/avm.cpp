#include "IOperand.hpp"
#include "Operand.hpp"
#include "Erreur.hpp"
#include "avm.hpp"
#include "factory.hpp"

token::token() : code(None)
{
}

token::~token()
{
}

avm::avm(std::istream &stream) : source(stream)
{
}

// On vidange la pile de token et la pile d'Operand
avm::~avm()
{
  int	i;
  int	size;

  i = 0;
  size = list_token.size();
  while (i < size)
    {
      delete list_token[i];
      i++;
    }
  list_token.clear();

  i = 0;
  size = pile.size();
  while (i < size)
    {
      delete pile[i];
      i++;
    }
  pile.clear();
}

/* ------------------------------------------------------------ */

void	avm::execute()
{
  int	i = 0;
  int	size = list_token.size();

  // this->dump_all_token(); // -- Affiche les tokens
  while (i < size)
    {
      switch (list_token[i]->code)
	{
	case Push:
	  this->push(*list_token[i]);
	  break;

	case Pop:
          this->pop();
          break;

	case Dump:
          this->dump();
          break;

	case Assert:
	  this->assert(*list_token[i]);
          break;

	case Add:
          this->add();
	  break;

	case Sub:
          this->sub();
          break;

	case Mul:
          this->mul();
          break;

	case Div:
          this->div();
          break;

	case Mod:
          this->mod();
          break;

	case Print:
          this->print();
          break;

	case Exit:
	  this->exit();
	  return;

	default:
	  std::cerr << "WUT ?!?" << std::endl;
	  break;
	}
      i++;
    }
  throw Erreur(NoExit);
}

/* ----------------------------------------------------------- */

void	avm::check_stack_size(const size_t size)
{
  if (this->pile.size() < size)
    throw Erreur(NoEnoughOperand);
}

void	avm::push(const token &token)
{
  IOperand	*ptr;

  if (token.type >= Float)
    ptr = factory::new_operand(token.valueD, token.type);
  else
    ptr = factory::new_operand(token.valueI, token.type);
  this->pile.push_back(ptr);
}

void	avm::pop()
{
  if (this->pile.size() == 0)
    throw Erreur(InvalidPop);
  delete this->pile.back();
  this->pile.pop_back();
}

void	avm::dump()
{
  std::vector<IOperand *>::reverse_iterator rit;

  for (rit = this->pile.rbegin(); rit < this->pile.rend(); rit++)
    std::cout << (*rit)->toString() << std::endl;
}

void	avm::assert(const token &token)
{
  IOperand	*ptr;

  this->check_stack_size(1);
  if (token.type != this->pile.back()->getType())
    throw Erreur(InvalidAssert);
  ptr = this->pile.back();

  switch (token.type)
    {
    case Float:
      if ((float)token.valueD != (float)getValueD(ptr->toString()))
	throw Erreur(InvalidAssert);
      break;

    case Double:
      if ((token.valueD != getValueD(ptr->toString())))
	throw Erreur(InvalidAssert);
      break;

    case Int8:
      if ((S8)token.valueI != (S8)getValueI(ptr->toString()))
	throw Erreur(InvalidAssert);
      break;

    case Int16:
      if ((S16)token.valueI != (S16)getValueI(ptr->toString()))
	throw Erreur(InvalidAssert);
      break;

    case Int32:
      if ((S32)token.valueI != (S32)getValueI(ptr->toString()))
	throw Erreur(InvalidAssert);
      break;
    }
}

void	avm::add()
{
  IOperand	*Op1;
  IOperand	*Op2;
  IOperand	*res;

  check_stack_size(2);
  Op2 = this->pile.back();
  this->pile.pop_back();
  Op1 = this->pile.back();
  this->pile.pop_back();

  res = *Op1 + *Op2;
  this->pile.push_back(res);
  delete Op1;
  delete Op2;
}

void	avm::sub()
{
  IOperand      *Op1;
  IOperand      *Op2;
  IOperand      *res;

  check_stack_size(2);
  Op2 = this->pile.back();
  this->pile.pop_back();
  Op1 = this->pile.back();
  this->pile.pop_back();

  res = *Op1 - *Op2;
  this->pile.push_back(res);
  delete Op1;
  delete Op2;
}

void	avm::mul()
{
  IOperand      *Op1;
  IOperand      *Op2;
  IOperand      *res;

  check_stack_size(2);
  Op2 = this->pile.back();
  this->pile.pop_back();
  Op1 = this->pile.back();
  this->pile.pop_back();

  res = *Op1 * *Op2;
  this->pile.push_back(res);
  delete Op1;
  delete Op2;
}


void	avm::div()
{
  IOperand      *Op1;
  IOperand      *Op2;
  IOperand      *res;

  check_stack_size(2);
  Op2 = this->pile.back();
  this->pile.pop_back();
  Op1 = this->pile.back();
  this->pile.pop_back();

  res = *Op1 / *Op2;
  this->pile.push_back(res);
  delete Op1;
  delete Op2;
}


void    avm::mod()
{
  IOperand      *Op1;
  IOperand      *Op2;
  IOperand      *res;

  check_stack_size(2);
  Op2 = this->pile.back();
  this->pile.pop_back();
  Op1 = this->pile.back();
  this->pile.pop_back();

  res = *Op1 % *Op2;
  this->pile.push_back(res);
  delete Op1;
  delete Op2;
}


void	avm::print()
{
  IOperand	*Op;

  check_stack_size(1);
  Op = this->pile.back();
  if (Op->getType() != Int8)
    throw Erreur(InvalidAssert, "Instruction Assert invalide - print");
  std::cout << (char)(getValueI(Op->toString())) << std::flush;
}

void	avm::exit()
{
}
