NAME = test.out
LIBUNIT = ../libunit.a
SRC = main.c \
		$(addprefix strlen/, 00_launcher.c  01_basic.c 02_null.c 03_long_string.c 04_short_string.c) \
		$(addprefix atoi/, 00_launcher.c  01_basic.c 02_null.c 03_partial_num.c 04_negative.c) \
		$(addprefix strcpy/, 00_launcher.c  01_basic.c)
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