NAME = test.out
LIBUNIT = ../libunit.a
ATOI = $(shell ls real_tests/ft_atoi)
STRLEN = $(shell ls real_tests/ft_strlen)
SRC = main.c \
		$(addprefix ft_strlen/, $(STRLEN))
		$(addprefix ft_atoi/, $(ATOI))
OBJ = $(SRC:.c=.o)
COMP = cc -g -Wall -Werror -Wextra

all: $(NAME)
	
$(NAME) : $(LIBUNIT) $(OBJ) 
	echo $(SRC)
	$(COMP) $(OBJ) $(LIBUNIT) -o $(NAME)

$(LIBUNIT):
	$(MAKE) -C ../

%.o: %.c
	$(COMP) -c $< -o $@

clean: 
	rm -f $(OBJ) $(OBJ_BONUS) *.out

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME)

.PHONY: all clean fclean re test
.SILENT: