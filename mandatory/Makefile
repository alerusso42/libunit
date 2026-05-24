NAME = libunit.a
LIBUNIT =  $(addprefix framework/, cleanup.c  error.c  launch_test.c  load_test.c  print_test.c)
LIBFT = $(addprefix libft/, ft_atoi.c ft_putnbr.c ft_strcmp.c ft_strlen.c)
SRC = $(LIBUNIT) $(LIBFT) 
OBJ_SRC = $(SRC:.c=.o)
OBJ_LIBFT = $(LIBFT:.c=.o)
OBJ = $(OBJ_SRC) $(OBJ_LIBFT)
COMP = cc -g -Wall -Werror -Wextra
SHELL := /bin/bash				
DIV = "\033[33m---------------------------\033[0m\n"
TABS = "-------"

all: $(NAME)

$(NAME) : $(OBJ)
	echo $(SRC)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(COMP) -c $< -o $@

clean: 
	rm -f $(OBJ) $(OBJ_BONUS) *.out
	$(MAKE) clean -C tests
	$(MAKE) clean -C real-tests

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C tests
	$(MAKE) fclean -C real-tests

re: fclean all

test: all
	clear
	@echo -e $(DIV) $(TABS) "TESTS" $(TABS) "\n" $(DIV)
	-$(MAKE) test -C tests
	@echo -e $(DIV) $(TABS) "REAL-TESTS" $(TABS) "\n" $(DIV)
	-$(MAKE) test -C real-tests

val: all
	clear
	@echo -e $(DIV) $(TABS) "TESTS" $(TABS) "\n" $(DIV)
	-$(MAKE) val -C tests
	@echo -e $(DIV) $(TABS) "REAL-TESTS" $(TABS) "\n" $(DIV)
	-$(MAKE) val -C real-tests

norm:
	clear
	@norminette | grep "Error!" || echo ""
	@norminette > /dev/null && echo -e "\033[32mNorminette OK\033[0m" || echo ""

.PHONY: all clean fclean re main gdb run valgrind val val_noflags