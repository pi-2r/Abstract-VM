NAME		= avm
CC		= g++
RM		= rm -f
ECHO		= echo -e

# Flags
CPPFLAGS	+= -Wall -Wextra -g
CPPFLAGS	+= -I include

SRC   = src/grammaire.cpp\
	src/getValue.cpp\
	src/Erreur.cpp\
	src/Operand.cpp\
	src/factory.cpp\
	src/avm.cpp\
	src/start_avm.cpp\
	src/main.cpp\
	src/dump_token.cpp


OBJ	= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CPPFLAGS) -o $(NAME)
	@$(ECHO) '\033[0;32m> Compiled\033[0m'

clean:
	$(RM) $(OBJ)
	@$(ECHO) '\033[0;35m> Directory cleaned\033[0m'

fclean:
	$(RM) $(NAME) $(OBJ)
	@$(ECHO) '\033[0;35m> Remove executable\033[0m'

re:
	make fclean
	make all

.PHONY: all clean fclean re