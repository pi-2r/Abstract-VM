#ifndef IOPERAND_HH_
#define IOPERAND_HH_

#include <string>
enum eOperandType { Int8 = 0, Int16 = 1, Int32 = 2, Float = 3, Double = 4 };

//classe abstraite                                
class IOperand
{
public:
  virtual std::string const &	toString() const = 0;  // Renvoie une string reprensentant l’instance

  virtual int			getPrecision() const = 0; // Renvoie la precision du type de l’instance
  virtual eOperandType		getType() const = 0; // Renvoie le type de l’instance. Voir plus bas

  virtual IOperand		*operator+(const IOperand &rhs) const = 0; // Somme
  virtual IOperand		*operator-(const IOperand &rhs) const = 0; // Difference
  virtual IOperand		*operator*(const IOperand &rhs) const = 0; // Produit
  virtual IOperand		*operator/(const IOperand &rhs) const = 0; // Quotient
  virtual IOperand		*operator%(const IOperand &rhs) const = 0; // Modulo

  virtual ~IOperand() {};
};

#endif
