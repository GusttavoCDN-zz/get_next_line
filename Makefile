NAME = get_next_line.a

SRCS = get_next_line.c get_next_line_utils.c

HEADER = .

RM = rm -f

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

CC = cc

all: ${NAME}

${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

clean:
	$(RM) ${OBJS}

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: clean all fclean re
