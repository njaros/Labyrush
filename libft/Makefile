SRCS = 	ft_isalnum.c \
		ft_isprint.c \
		ft_memcmp.c \
		ft_putchar_fd.c \
		ft_split.c \
		ft_striteri.c \
		ft_strlen.c \
		ft_strrchr.c \
		ft_toupper.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_isalpha.c \
		ft_memcpy.c \
		ft_putendl_fd.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_strmapi.c \
		ft_strtrim.c \
		ft_bzero.c \
		ft_isascii.c \
		ft_memmove.c \
		ft_putnbr_fd.c \
		ft_strcpy.c \
		ft_strlcat.c \
		ft_strncmp.c \
		ft_substr.c \
		ft_calloc.c \
		ft_isdigit.c \
		ft_memchr.c \
		ft_memset.c \
		ft_strcmp.c \
		ft_putstr_fd.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strnstr.c \
		ft_switch.c \
		ft_tolower.c \
		ft_lstclear.c \
		ft_lstmap.c \
		ft_lstdelone.c \
		ft_lstnew.c \
		ft_lstadd_back.c \
		ft_lstiter.c \
		ft_lstsize.c \
		ft_lstadd_front.c \
		ft_lstlast.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_int.c \
		ft_printf.c \
		ft_putadr.c \
		ft_putchar_printf.c \
		ft_puthexa_fd.c \
		ft_putnbr_printf.c \
		ft_putstr_printf.c \
		ft_putunsignedint_fd.c \
		ft_read.c \
		ft_unsignedint.c
OBJS = ${SRCS:.c=.o}
HEADERS_PATH = ../includes
HEADERS = ../includes/libft.h
NAME = libft.a
RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=30

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${HEADERS_PATH}

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS} 

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all clean flclean re
