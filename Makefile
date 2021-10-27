# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 21:17:45 by cbeaurai          #+#    #+#              #
#    Updated: 2021/10/27 10:22:42 by cbeaurai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS		= readline.c utils.c builtin/utils.c builtin/cd.c builtin/echo.c \
				builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c \
				builtin/unset.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc

RM			= rm -rf

LFT			= ./libft

CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address -I.

LIBS		= -lreadline -L ./libft -lft

MAKE_LIB	= ${MAKE} -C ${LFT}

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE_LIB)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:		
			$(RM) $(OBJS)
			$(MAKE_LIB) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE_LIB) fclean

re:		fclean $(NAME)

.PHONY:		all clean fclean re
