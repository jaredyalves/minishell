CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I.

NAME = minishell
SRCS = ft/ft_split.c lexer/backcmd.c lexer/execcmd.c lexer/listcmd.c lexer/pipecmd.c lexer/redicmd.c minishell.c nulterminate/nulback.c nulterminate/nulexec.c nulterminate/nullist.c nulterminate/nulpipe.c nulterminate/nulredi.c nulterminate/nulterminate.c parser/parseblock.c parser/parsecmd.c parser/parseexec.c parser/parseline.c parser/parsepipe.c parser/parseredir.c parser/utils.c run/freecmd.c run/runback.c run/runcmd.c run/runexec.c run/runlist.c run/runpipe.c run/runredi.c utils.c
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
