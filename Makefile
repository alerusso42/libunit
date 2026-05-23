NAME = libunit.a
LIBUNIT =  $(addprefix framework/, cleanup.c  error.c  launch_test.c  load_test.c  print_test.c)
LIBFT = $(addprefix libft/, ft_strlen.c)
SRC = $(LIBUNIT) $(LIBFT)
# SRC_BONUS = 
OBJ_SRC = $(SRC:.c=.o)
OBJ_LIBFT = $(LIBFT:.c=.o)
OBJ = $(OBJ_SRC) $(OBJ_LIBFT)
# OBJ_BONUS = $(SRC_BONUS:.c=.o)
COMP = cc -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME) : $(OBJ)
# 	cp $(LIBFT) $(NAME)
	echo $(SRC)
	ar rcs $(NAME) $(OBJ)

# bonus: $(LIBFT) $(OBJ_BONUS)
# 	cp $(LIBFT) $(NAME)
# 	ar rcs $(NAME) $(OBJ_BONUS)

# $(LIBFT) : 
# 	$(MAKE) -C $(LIBFT_RELATIVE_PATH)

%.o: %.c
	$(COMP) -c $< -o $@

clean: 
	rm -f $(OBJ) $(OBJ_BONUS) *.out
	$(MAKE) clean -C tests
# 	$(MAKE) clean -C $(LIBFT_RELATIVE_PATH)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C tests
# 	$(MAKE) fclean -C $(LIBFT_RELATIVE_PATH)

re: fclean all

test: all
	$(MAKE) test -C tests

val: all
	clear
	$(MAKE) val -C tests


.PHONY: all clean fclean re main gdb run valgrind val val_noflags