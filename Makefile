NAME = libunit.a
LIBUNIT = 
SRC = $(addprefix framework/, cleanup.c  error.c  launch_test.c  load_test.c  print_test.c)
# SRC_BONUS = 
OBJ = $(SRC:.c=.o)
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
# 	$(MAKE) clean -C $(LIBFT_RELATIVE_PATH)

fclean: clean
	rm -f $(NAME)
# 	$(MAKE) fclean -C $(LIBFT_RELATIVE_PATH)

re: fclean all

test: all
	echo "tester"

# val: re clean
# 	$(COMP) main.c $(NAME)
# 	clear
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./a.out


.PHONY: all clean fclean re main gdb run valgrind val val_noflags