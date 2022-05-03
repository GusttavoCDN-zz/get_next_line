NAME = get_next_line.a

SRCS = get_next_line.c get_next_line_utils.c

HEADER = get_next_line.h

RM = rm -f

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

CC = cc

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	ar -rcs ${NAME} ${OBJS} ${HEADER}

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) ${OBJS}

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: clean all fclean re
