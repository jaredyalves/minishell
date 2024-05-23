CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I./include

NAME = minishell
SRCS = \
	src/ft/ft_split.c \
	src/lexer/backcmd.c \
	src/lexer/execcmd.c \
	src/lexer/listcmd.c \
	src/lexer/pipecmd.c \
	src/lexer/redicmd.c \
	src/nulterminate/nulback.c \
	src/nulterminate/nulexec.c \
	src/nulterminate/nullist.c \
	src/nulterminate/nulpipe.c \
	src/nulterminate/nulredi.c \
	src/nulterminate/nulterminate.c \
	src/parser/parseblock.c \
	src/parser/parsecmd.c \
	src/parser/parseexec.c \
	src/parser/parseline.c \
	src/parser/parsepipe.c \
	src/parser/parseredir.c \
	src/parser/utils.c \
	src/run/freecmd.c \
	src/run/runback.c \
	src/run/runcmd.c \
	src/run/runexec.c \
	src/run/runlist.c \
	src/run/runpipe.c \
	src/run/runredi.c \
	src/utils.c \
	src/minishell.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re valgrind sanitize

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

valgrind: CFLAGS += -g3
valgrind: re
	valgrind\
		--leak-check=full\
		--show-leak-kinds=all\
		--track-origins=yes\
		--track-fds=yes\
		--trace-children=yes\
		./$(NAME)

sanitize: CFLAGS += -g -fsanitize=address
sanitize: re
	./$(NAME)

# vim: ts=4 sts=4 sw=4 noet
