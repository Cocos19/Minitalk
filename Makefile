# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 11:14:30 by mprofett          #+#    #+#              #
#    Updated: 2022/12/09 11:14:32 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME			= client

CLIENT_SRC			= client.c

CLIENT_OBJ			= ${CLIENT_SRC:.c=.o}

SERVER_NAME			= server

SERVER_SRC			= server.c

SERVER_OBJ			= ${SERVER_SRC:.c=.o}

CLIENT_NAME_BONUS	= client

CLIENT_SRC_BONUS	= client_bonus.c

CLIENT_OBJ_BONUS	= ${CLIENT_SRC_BONUS:.c=.o}

SERVER_NAME_BONUS	= server

SERVER_SRC_BONUS	= server_bonus.c

SERVER_OBJ_BONUS	= ${SERVER_SRC_BONUS:.c=.o}

LIB_NAME	= libft.a

LIB_PATH	= ./libft

CC			= gcc

RM			= rm -f

CFLAGS	= -Wall -Wextra -Werror

all: ${LIB_NAME} ${CLIENT_NAME} ${SERVER_NAME}

${LIB_NAME}:
	${MAKE} bonus -C ${LIB_PATH}
	mv ${LIB_PATH}/${LIB_NAME} .

${CLIENT_NAME}: ${CLIENT_OBJ}
	${CC} ${CFLAGS} ${LIB_NAME} ${CLIENT_OBJ} -o ${CLIENT_NAME}

${SERVER_NAME}: ${SERVER_OBJ}
	${CC} ${CFLAGS} ${LIB_NAME} ${SERVER_OBJ} -o ${SERVER_NAME}

bonus: ${LIB_NAME} ${CLIENT_OBJ_BONUS} ${SERVER_OBJ_BONUS}
	${CC} ${CFLAGS} ${LIB_NAME} ${CLIENT_OBJ_BONUS} -o ${CLIENT_NAME_BONUS}
	${CC} ${CFLAGS} ${LIB_NAME} ${SERVER_OBJ_BONUS} -o ${SERVER_NAME_BONUS}

clean:
	${MAKE} clean -C ${LIB_PATH}
	${RM} ${CLIENT_OBJ} ${SERVER_OBJ} ${CLIENT_OBJ_BONUS} ${SERVER_OBJ_BONUS}

fclean: clean
	${RM} ${CLIENT_NAME} ${SERVER_NAME} ${LIB_NAME}

re:	fclean all

.PHONY:	all bonus clean fclean re
