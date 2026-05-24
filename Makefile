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

.PHONY: all clean fclean re