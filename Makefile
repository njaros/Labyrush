# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:47:18 by njaros            #+#    #+#              #
#    Updated: 2023/01/06 11:58:31 by njaros           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

## LES INCONTOURNABLES ##

NAME = labyrush
CC = gcc
FLAGS = -Wall -Wextra -Wall

## LES CHEMINS ##

PATH_SRCS = src
PATH_OBJS = obj
PATH_INCLUDES = includes

## LES CHEMINS DES LIBRAIRIES ##

LIB = libft/libft.a
PINGPONG = pingpong
## LES SOURCES, OBJETS et INCLUDES ##

LST_SRCS =	main.c \
			a_star.c \
			mazer.c \
			mazer_v2.c \
			keskiladi.c \
			pied.c

LST_OBJS = ${LST_SRCS:.c=.o}

LST_INCLUDES =	labyrush.h \
				libft.h

SRC =		$(addprefix ${PATH_SRCS}/,${LST_SRCS})
OBJS =		$(addprefix ${PATH_OBJS}/,${LST_OBJS})
INCLUDES =	$(addprefix ${PATH_INCLUDES}/,${LST_INCLUDES})
## LES REGLES DE COMPILATION DU PROGRAMME ##

all :				Makefile ${LIB} ${NAME}

solver :			src/solver.cpp
					c++ -Wall -Wextra -Werror src/solver.cpp -o solver

pingpong :
					${PINGPONG}

${NAME} :			${OBJS} ${PINGPONG}
					${CC} ${FLAGS} ${OBJS} ${LIB} -pthread -o $@

${PATH_OBJS}/%.o:	${PATH_SRCS}/%.c ${INCLUDES} ${LIB} Makefile | ${PATH_OBJS}
					${CC} ${FLAGS} -c $< -o $@ -I ${PATH_INCLUDES}

${PATH_OBJS}:
					mkdir obj

## APPELS D'AUTRES MAKEFILES ##

${LIB}:
					make -C ./libft

${PINGPONG} :		
					make -C ./pingpong_dir

## LES REGLES DE SUPPRESSION ET RE ##

clean:
					make clean -C ./libft
					rm -rf obj

fclean:				clean
					make fclean -C ./libft
					rm -f ${NAME} pingpong solver result.log output.log

re:					fclean all

## LE TRUC ##

.PHONY: all re clean fclean

## FIN ##