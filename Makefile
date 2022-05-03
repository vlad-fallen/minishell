# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 15:40:50 by mbutter           #+#    #+#              #
#    Updated: 2022/05/03 16:44:35 by echrysta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	main.c \
				env_init.c \
				token_list.c \
				lexer_token_utils.c \
				lexer_token.c \
				lexer.c\
				signal.c\
				dollar_pars.c\
				print_list_token.c

OBJS		=	$(patsubst %.c,%.o,$(SRCS)) 

BONUS		=	

BONUS_OBJS	=	$(patsubst %.c,%.o,$(BONUS))

D_FILES		=	$(patsubst %.c,%.d,$(SRCS) $(BONUS)) 

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

NAME		=	minishell

LIBFT_NAME	=	./libft/libft.a


%.o:		%.c
			$(CC) $(CFLAGS) -I ./libft/ -c $< -o $@ -MMD

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT_NAME)
			$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT_NAME) -o $(NAME)

$(LIBFT_NAME):
			@make -C ./libft bonus

clean:
			$(RM) $(OBJS) $(D_FILES) $(BONUS_OBJS) $(D_FILES_B)
			@make -C ./libft clean

fclean:		clean
			$(RM) $(NAME)
			@make -C ./libft fclean

re:			fclean $(NAME)

bonus:		

.PHONY:		all clean fclean re bonus

include $(wildcard $(D_FILES))
