#include <iostream>
#include <sstream>
#include <math.h>
#include "Operand.hpp"
#include "factory.hpp"
#include "Erreur.hpp"

//Les templates c'est la vie :)
template<typename T>
Operand<T>::~Operand()
{
}

template<typename T>
Operand<T>::Operand() : _type(Int8)
{
  throw Erreur(NoEnoughOperand);
}

static S32      check_addition(const IOperand &first, const IOperand &second);
static S32      check_soustraction(const IOperand &first, const IOperand &second);
static S32      check_multiplication(const IOperand &first, const IOperand &second);
static S32      check_division(const IOperand &first, const IOperand &second);
static S32	check_modulo(const IOperand &first, const IOperand &second);


/* ----------------------------------------------- */
/*                  Constructeur                   */

template<>
Operand<S8>::Operand(signed char nb) : _type(Int8)
{
  std::ostringstream	buffer(std::ostringstream::out);

  buffer << (int)nb << std::flush;
  this->_StringValue = buffer.str();
}

template<>
Operand<S16>::Operand(S16 nb) : _type(Int16)
{
  std::ostringstream    buffer(std::ostringstream::out);

  buffer << nb << std::flush;
  this->_StringValue = buffer.str();
}

template<>
Operand<S32>::Operand(S32 nb) : _type(Int32)
{
  std::ostringstream    buffer(std::ostringstream::out);

  buffer << nb << std::flush;
  this->_StringValue = buffer.str();
}

template<>
Operand<float>::Operand(float nb) : _type(Float)
{
  std::ostringstream    buffer(std::ostringstream::out);

  buffer << nb << std::flush;
  this->_StringValue = buffer.str();
}

template<>
Operand<double>::Operand(double nb) : _type(Double)
{
  std::ostringstream    buffer(std::ostringstream::out);

  buffer << nb << std::flush;
  this->_StringValue = buffer.str();
}


/* --------------------------------------------- */
/* --------------------------------------------- */

template<typename T>
const std::string	&Operand<T>::toString() const
{
  return this->_StringValue;
}

template<typename T>
int			Operand<T>::getPrecision() const
{
  return this->_type;
}

template<typename T>
eOperandType		Operand<T>::getType() const
{
  return this->_type;
}

template<typename T>
IOperand		*Operand<T>::operator+(const IOperand &rhs) const
{
  IOperand		*ptr;

  if (rhs.getPrecision() >= Float || this->getPrecision() >= Float)
    {
      double		value;

      value = getValueD(this->toString()) + getValueD(rhs.toString());
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  else
    {
      S32		value;

      value = check_addition(*this, rhs);
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  return ptr;
}

template<typename T>
IOperand		*Operand<T>::operator-(const IOperand &rhs) const
{
  IOperand              *ptr;

  if (rhs.getPrecision() >= Float || this->getPrecision() >= Float)
    {
      double		value;

      value = getValueD(this->toString()) - getValueD(rhs.toString());
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  else
    {
      S32		value;

      value = check_soustraction(*this, rhs);
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  return ptr;
}

template<typename T>
IOperand		*Operand<T>::operator*(const IOperand &rhs) const
{
  IOperand              *ptr;

  if (rhs.getPrecision() >= Float || this->getPrecision() >= Float)
    {
      double		value;

      value = getValueD(this->toString()) * getValueD(rhs.toString());
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  else
    {
      S32		value;

      value = check_multiplication(*this, rhs);
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  return ptr;
}

template<typename T>
IOperand		*Operand<T>::operator/(const IOperand &rhs) const
{
  IOperand              *ptr;

  if (rhs.getPrecision() >= Float || this->getPrecision() >= Float)
    {
      double		value;

      if (getValueD(rhs.toString()) == 0)
	throw Erreur(DivByZero);
      value = getValueD(this->toString()) / getValueD(rhs.toString());
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  else
    {
      S32		value;

      if (getValueI(rhs.toString()) == 0)
	throw Erreur(DivByZero);
      value = check_division(*this, rhs);
      if (this->getPrecision() >= rhs.getPrecision())
	ptr = factory::new_operand(value, this->getType());
      else
	ptr = factory::new_operand(value, rhs.getType());
    }
  return ptr;
}

template<typename T>
IOperand		*Operand<T>::operator%(const IOperand &rhs) const
{
  IOperand              *ptr;


  if (rhs.getPrecision() >= Float || this->getPrecision() >= Float)
    {
      double            value;

      if (getValueD(rhs.toString()) == 0)
	throw Erreur(DivByZero);
      value = fmod(getValueD(this->toString()), getValueD(rhs.toString()));
      if (this->getPrecision() >= rhs.getPrecision())
        ptr = factory::new_operand(value, this->getType());
      else
        ptr = factory::new_operand(value, rhs.getType());
    }
  else
    {
      S32               value;

      if (getValueI(rhs.toString()) == 0)
	throw Erreur(DivByZero);
      value = check_modulo(*this, rhs);
      if (this->getPrecision() >= rhs.getPrecision())
        ptr = factory::new_operand(value, this->getType());
      else
        ptr = factory::new_operand(value, rhs.getType());
    }
  return ptr;

}

template class Operand <S8>;
template class Operand <S16>;
template class Operand <S32>;
template class Operand <float>;
template class Operand <double>;

/* --------------------------------- check_op ------------------------------- */

S32	check_addition(const IOperand &first, const IOperand &second)
{
  S32	value1 = getValueI(first.toString());
  S32	value2 = getValueI(second.toString());
  S32	result = value1 + value2;

  if (first.getType() == Int16 || second.getType() == Int16)
    result = (S16)result;
  else if (first.getType() == Int8 || second.getType() == Int8)
    result = (S8)result;

  if (value1 == 0 || value2 == 0);
  else if (value1 > 0 && value2 > 0)
    {
      if (result < value1 || result < value2)
	throw Erreur(Overflow);
    }
  else if (getValueI(first.toString()) < 0 && getValueI(second.toString()) < 0)
    {
      if (result > value1 || result > value2)
	throw Erreur(Underflow);
    }
  return result;
}

S32		check_soustraction(const IOperand &first, const IOperand &second)
{
  S32		value1 = getValueI(first.toString());
  S32		value2 = getValueI(second.toString());
  long long	result = (long long)value1 - (long long)value2;

  if (first.getType() == Int16 || second.getType() == Int16)
    {
      if ((S16)result != result)
	throw Erreur(Overflow);
      return ((S16)result);
    }
  else if (first.getType() == Int8 || second.getType() == Int8)
    {
      if ((S8)result != result)
	throw Erreur(Overflow);
      return ((S8)result);
    }
  else
    {
      if ((S32)result != result)
	throw Erreur(Overflow);
      return ((S32)result);
    }
}

S32		check_multiplication(const IOperand &first, const IOperand &second)
{
  S32		value1 = getValueI(first.toString());
  S32		value2 = getValueI(second.toString());
  long long	result = (long long)value1 * (long long) value2;

  if (first.getType() == Int32 || second.getType() == Int32)
    {
      if ((S32)result != result)
	throw Erreur(Overflow);
      else if (result / (long long)value2 != (long long)value1)
	throw Erreur(Overflow);
      return (S32)result;
    }
  else if (first.getType() == Int16 || second.getType() == Int16)
    {
      if ((S16)result != result)
	throw Erreur(Overflow);
      else if (result /(long long)value2 != (long long)value1)
	throw Erreur(Overflow);
      return (S16)result;
    }
  else
    {
      if ((S8)result != result)
	throw Erreur(Overflow);
      else if (result /(long long)value2 != (long long)value1)
	throw Erreur(Overflow);
      return (S8)result;
    }
}

S32		check_division(const IOperand &first, const IOperand &second)
{
  S32           value1 = getValueI(first.toString());
  S32           value2 = getValueI(second.toString());
  long long     result;

  result = (long long)value1 / (long long)value2;
  if (first.getType() == Int32 || second.getType() == Int32)
    return (S32)result;
  else if (first.getType() == Int16 || second.getType() == Int16)
    return (S16)result;
  else
    return (S8)result;
}


S32		check_modulo(const IOperand &first, const IOperand &second)
{
  S32           value1 = getValueI(first.toString());
  S32           value2 = getValueI(second.toString());
  long long     result;

  result = (long long)value1 % (long long)value2;
  if (first.getType() == Int32 || second.getType() == Int32)
    return (S32)result;
  else if (first.getType() == Int16 || second.getType() == Int16)
    return (S16)result;
  else
    return (S8)result;
}
