CC = gcc
SRCS = minishell.c
NAME = minishell
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
%.o:%.c *.h
	$(CC) $(CFLAGS) -c $< -o $@
all		: *.h
	@$(MAKE) $(NAME)
$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)
clean	:
	rm -rf *.o
fclean	: clean
	rm -rf $(NAME)
re: fclean all

.PHONY	: all clean fclean re