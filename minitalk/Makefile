
SERVER	= server
CLIENT	= client

SRCS_SERVER	= server.c fonctions.c
SRCS_CLIENT	= client.c fonctions.c

OBJS_SERVER	= ${SRCS_SERVER:.c=.o}
OBJS_CLIENT	= ${SRCS_CLIENT:.c=.o}

NAME		= ${SERVER} ${CLIENT}

CC 	= gcc

RM	= rm -f

CFLAGS	=  -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

bonus:		re

${NAME}:	${OBJS_SERVER} ${OBJS_CLIENT}
			${CC} ${CFLAGS} -o ${SERVER} ${OBJS_SERVER}
			${CC} ${CFLAGS} -o ${CLIENT} ${OBJS_CLIENT}

clean:		
			${RM} ${OBJS_SERVER} ${OBJS_CLIENT}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus\