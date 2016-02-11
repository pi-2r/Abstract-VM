#ifndef ERREUR_HH_
#define ERREUR_HH_

#include <string>
#include <exception>

enum ErreurType { SyntaxError, UnknowInstruction, Overflow, Underflow, InvalidPop,
		  DivByZero, NoExit, InvalidAssert, NoEnoughOperand, UnknowError };

class Erreur : public std::exception
{
public:
  Erreur(const ErreurType type, const std::string str = "") throw();
  ~Erreur() throw();
  virtual const char	*what() const throw();

private:
  const ErreurType	_type;
  const std::string	_str;

private:
  Erreur();
};

#endif