SRC = main.c\
	$(addprefix module2/, $(shell ls module2 | grep '\.c'))\
	$(addprefix module1/, $(shell ls module1 | grep '\.c'))\
	$(addprefix ft_printf/, $(shell ls ft_printf | grep '\.c'))
NAME = test.out
LIBUNIT = ../libunit.a
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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --child-silent-after-fork=yes --trace-children=no --track-fds=yes  -s ./$(NAME)

.PHONY: all clean fclean re test
.SILENT:
