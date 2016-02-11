#ifndef OPERAND_HPP_
#define OPERAND_HPP_

#include "IOperand.hpp"
#include "getValue.hpp"
#include "type.hpp"

template<typename T>
class Operand : public IOperand
{
private:
  Operand();
  Operand(const Operand &other);

public:
  Operand(T nb);
  ~Operand();

private:
  std::string			_StringValue;
  const eOperandType		_type;

public:
  virtual const std::string	&toString() const;

  virtual int			getPrecision() const;
  virtual eOperandType		getType() const;

  virtual IOperand		*operator+(const IOperand &rhs) const;
  virtual IOperand		*operator-(const IOperand &rhs) const;
  virtual IOperand		*operator*(const IOperand &rhs) const;
  virtual IOperand		*operator/(const IOperand &rhs) const;
  virtual IOperand		*operator%(const IOperand &rhs) const;
};

#endif /* OPERAND_HPP_ */
