NAME = test.out
LIBUNIT = ../libunit.a
SRC = main.c \
		$(addprefix ft_strlen/, $(shell ls ft_strlen | grep '\.c'))\
		$(addprefix ft_atoi/, $(shell ls ft_atoi | grep '\.c'))
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