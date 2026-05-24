all: 
	$(MAKE) all -C mandatory/

bonus:
	$(MAKE) all -C bonus/

clean: 
	$(MAKE) clean -C mandatory/
	$(MAKE) clean -C bonus/

fclean: clean
	$(MAKE) fclean -C mandatory/
	$(MAKE) fclean -C bonus/

test:
	$(MAKE) test -C mandatory/

bonus_test:
	$(MAKE) test -C bonus/

re: fclean all

norm: 
	clear
	$(MAKE) norm -C mandatory/
	$(MAKE) norm -C bonus/

val:
	clear
	$(MAKE) val -C mandatory/
	$(MAKE) val -C bonus/

.PHONY: all clean fclean re norm val test bonus_test bonus