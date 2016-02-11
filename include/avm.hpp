#ifndef CORE_AVM_HH_
#define CORE_AVM_HH_

#include <string>
#include <iostream>
#include <vector>
#include "IOperand.hpp"

/*
** start_avm s'occupe d'ouvrir et de fermer le fichier et d'envoyer un istream
*/
bool	start_avm(const char *path);

/*
** Lit - tokenise - execute
*/
void	core_avm(std::istream &stream);

enum		Instruction { Push, Pop, Dump, Assert, Add, Sub, Mul, Div, Mod, Print, Exit, None };
class		token
{
public:
  token();
  ~token();

  Instruction	code;
  eOperandType	type;
  double	valueD ;
  int		valueI ;

public:
  void	dump();
};

class	avm
{
public:
  avm(std::istream &stream);
  ~avm();

private:
  avm();

private:
  std::istream			&source;
  std::vector<IOperand *>	pile;
  std::vector<std::string>	vector_str;
  std::vector<token *>		list_token;

public:
  void	read_stream();
  void	tokenise();
  void	execute();

private:
  void	check_stack_size(const size_t size);

  /* ---- Dans grammaire.cpp ---- */
  void	tokenise_str(const std::string &str);
  void	remove_comment();
  bool	token_nomore_arg(std::istringstream &buffer, std::string &instr);
  void	token_get_instruction(const std::string &str, token &token);
  void	token_get_value(const std::string &str, token &token);
  void	token_num_check_gram(const std::string &str, const token &token);
  void	token_get_num(const std::string &str, token &token);
  void	token_check_implicit_overflow(const token &token);
  void	token_check_bad_conversion(const std::string &value, const token &token);
  eOperandType	token_get_type(const std::string &str, const size_t pos_val);
  void	dump_all_token();

  /* ---- Dans avm.cpp ---- */
  void	push(const token &token);
  void	pop();
  void	dump();
  void	assert(const token &token);
  void	add();
  void	sub();
  void	mul();
  void	div();
  void	mod();
  void	print();
  void	exit();
};
#endif