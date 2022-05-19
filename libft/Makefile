# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:42:55 by mbutter           #+#    #+#              #
#    Updated: 2022/05/03 13:49:14 by mbutter          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				get_next_line.c 

OBJS		=	$(SRCS:.c=.o)

BONUS		=	ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c

BONUS_OBJS	=	$(BONUS:.c=.o)

D_FILES		=	$(patsubst %.c,%.d,$(SRCS)) 

D_FILES_B	=	$(patsubst %.c,%.d,$(BONUS))

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -I ./

NAME		=	libft.a

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -MMD

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS) $(BONUS_OBJS) $(D_FILES) $(D_FILES_B)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

bonus:		$(OBJS) $(BONUS_OBJS)
			ar rc $(NAME) $(OBJS) $(BONUS_OBJS)
			ranlib $(NAME)

.PHONY:		all clean fclean re bonus

include $(wildcard $(D_FILES))