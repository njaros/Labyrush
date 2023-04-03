NAME = pingpong
CC = gcc
CPP = c++
FLAGS = -Wall -Wextra -Werror

PATH_SRCS = src
PATH_OBJS = obj
PATH_INCLUDES = includes

LST_SRCS =	pingpong.c
LST_OBJS =	${LST_SRCS:.c=.o}

SRC =		$(addprefix ${PATH_SRCS}/,${LST_SRCS})
OBJS =		$(addprefix ${PATH_OBJS}/,${LST_OBJS})

all :				${NAME} Makefile

${NAME} :			${OBJS}
					${CC} ${FLAGS} ${OBJS} -o ../$@

${PATH_OBJS}/%.o:	${PATH_SRCS}/%.c ${INCLUDES} Makefile | ${PATH_OBJS}
					${CC} ${FLAGS} -c $< -o $@

${PATH_OBJS}:
					mkdir obj

clean :
					rm -rf obj

fclean :			clean
					rm -f ${NAME} ping pong

re :				fclean all

.PHONY: all re clean fclean