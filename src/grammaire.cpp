#include <cmath>
#include <sstream>
#include "type.hpp"
#include "Erreur.hpp"
#include "avm.hpp"

void    avm::read_stream()
{
  char          buffer[2048];
  std::string   line;

  while (1)
    {
      this->source.getline(buffer, 2046, '\n');
      line = buffer;
      if (line.size() == 0 && this->source.eof())
        break;
      else if (this->source == std::cin && line.compare(";;") == 0)
        break;
      this->vector_str.push_back(line);
    }
  this->remove_comment();
}

void    avm::remove_comment()
{
  int           size = vector_str.size();
  int           i = 0;
  size_t        pos;

  while (i < size)
    {
      pos = vector_str[i].find_first_of(";");
      if (pos != std::string::npos)
        vector_str[i].erase(pos);
      i++;
    }
}

void	avm::token_get_instruction(const std::string &str, token &token)
{
  if (str.compare("push") == 0)
    token.code = Push;
  else if (str.compare("pop") == 0)
    token.code = Pop;
  else if (str.compare("dump") == 0)
    token.code = Dump;
  else if (str.compare("assert") == 0)
    token.code = Assert;
  else if (str.compare("add") == 0)
    token.code = Add;
  else if (str.compare("sub") == 0)
    token.code = Sub;
  else if (str.compare("mul") == 0)
    token.code = Mul;
  else if (str.compare("div") == 0)
    token.code = Div;
  else if (str.compare("mod") == 0)
    token.code = Mod;
  else if (str.compare("print") == 0)
    token.code = Print;
  else if (str.compare("exit") == 0)
    token.code = Exit;
  else
    throw Erreur(UnknowInstruction);
}

bool	avm::token_nomore_arg(std::istringstream &buffer, std::string &instr)
{
  instr.erase();
  buffer >> instr;
  if (instr.compare("") != 0)
    throw Erreur(SyntaxError, "Caracteres supplémentaires présent");
  else if (buffer.eof() == false)
    throw Erreur(SyntaxError, "Erreur de syntaxe : eof non atteinte (existe ?)");
  return true;
}

// L'important
void	avm::tokenise_str(const std::string &str)
{
  std::istringstream    buffer(str, std::istringstream::in);
  std::string		instr;
  token			*ptoken;

  buffer >> instr;
  if (instr.compare("") == 0 && buffer.eof())
    return;

  ptoken = new token;
  this->list_token.push_back(ptoken);

  this->token_get_instruction(instr, *ptoken);
  if ((ptoken->code != Push && ptoken->code != Assert))
    if (token_nomore_arg(buffer, instr))
      return;

  instr.erase();
  buffer >> instr;
  this->token_get_value(instr, *ptoken);
  token_nomore_arg(buffer, instr);
}

eOperandType	avm::token_get_type(const std::string &str, const size_t pos_par)
{
  std::string	type;

  type = str.substr(0, pos_par);

  if (type.compare("int32") == 0)
    return Int32;
  else if (type.compare("double") == 0)
    return Double;
  else if (type.compare("float") == 0)
    return Float;
  else if (type.compare("int16") == 0)
    return Int16;
  else if (type.compare("int8") == 0)
    return Int8;
  else
    throw Erreur(UnknowInstruction);
}

void	avm::token_num_check_gram(const std::string &str, const token &token)
{
  int	i;
  int	size = str.size();

  i = (str[0] == '-' ? 1 : 0);
  if (size <= (i ? 1 : 0))
    throw Erreur(SyntaxError);
  if (token.type >= Float)
    {
      if (str.find(".") == std::string::npos)
	throw Erreur(SyntaxError, "Erreur de syntaxe - . manquant (float)");
      else if (str.find_first_of(".") != str.find_last_of("."))
	throw Erreur(SyntaxError, "Multiples . présents");
      else if (str.find(".") == str.size() - 1)
	throw Erreur(SyntaxError, "Float mal formé");
      else if (str.at(i) == '.')
	throw Erreur(SyntaxError, "Float mal formé");
    }
  else
    {
      if (str.find(".") != std::string::npos)
	throw Erreur(SyntaxError);
    }
  while (i < size)
    {
      if ((str[i] >= '0' && str[i] <= '9'));
      else if (token.type >= Float && str[i] == '.');
      else
	throw Erreur(SyntaxError, "Erreur de syntaxe - nombre incorrect");
      i++;
    }
}

void	avm::token_get_num(const std::string &str, token &token)
{
  std::istringstream    buffer(std::istringstream::in);

  token_num_check_gram(str, token);
  buffer.str(str);
  switch (token.type)
    {
    case Double:
    case Float:
      buffer >> token.valueD;
      break;

    case Int8:
    case Int16:
    case Int32:
      if (str.find(".") != std::string::npos)
	throw Erreur(SyntaxError, "Erreur de syntaxe - double à la place d'un entier");
      buffer >> token.valueI;
      break;
    }
  if (token.type <= Int32)
    token_check_bad_conversion(str, token);
}

void	avm::token_check_bad_conversion(const std::string &value, const token &token)
{
  std::ostringstream	buffer(std::ostringstream::out);

  buffer << token.valueI;
  if (value.compare(buffer.str()) != 0)
    throw Erreur(Overflow, "Overflow implicite - Mauvaise conversion");
}

void	avm::token_get_value(const std::string &str, token &token)
{
  size_t	pos_val;
  size_t	pos_end;
  std::string	result;

  if (str.find("(") == std::string::npos || str.find(")") == std::string::npos)
    throw Erreur(SyntaxError, "Pas de parenthèses");
  if ((pos_end = str.find_last_of(")")) != str.find_first_of(")"))
    throw Erreur(SyntaxError, ") invalide");
  result = str.substr(pos_end + 1);
  if (result.compare("") != 0)
    throw Erreur(SyntaxError, "Caracteres excédentaires");
  if ((pos_val = str.find_first_of("(")) != str.find_last_of("("))
    throw Erreur(SyntaxError, "( invalide");

  token.type = token_get_type(str, pos_val);
  result.erase();
  result = str.substr(pos_val + 1);
  result.erase(result.find(")"));
  token_get_num(result, token);
  token_check_implicit_overflow(token);
}

void	avm::token_check_implicit_overflow(const token &token)
{
  if (token.code == Push || token.code == Assert)
    {
      if (token.type == Float)
	{
	  if (isinf((float)token.valueD))
	    throw Erreur(Overflow, "Overflow implicite");
	}
      else if (token.type == Int16)
	{
	  if ((S16)token.valueI != (S32)token.valueI)
	    throw Erreur(Overflow, "Overflow implicite");
	}
      else if (token.type == Int8)
	{
	  if ((S8)token.valueI != (S32)token.valueI)
	    throw Erreur(Overflow, "Overflow implicite");
	}
    }
}

void    avm::tokenise()
{
  int	i = 0;
  int	size = this->vector_str.size();

  while (i < size)
    {
      this->tokenise_str(vector_str[i]);
      i++;
    }
}
