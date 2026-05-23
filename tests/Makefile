NAME = test.out
LIBUNIT = ../libunit.a
SRC = main.c $(addprefix strlen/, 00_launcher.c  01_basic.c)
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
	echo "tester"

.PHONY: all clean fclean re main gdb run valgrind val val_noflags