NAME = minishell

SRCS = \
	src/ft/ft_dprintf.c \
	src/ft/ft_memset.c \
	src/ft/ft_split.c \
	src/ft/ft_strlen.c \
	src/lexer/backcmd.c \
	src/lexer/execcmd.c \
	src/lexer/listcmd.c \
	src/lexer/pipecmd.c \
	src/lexer/redicmd.c \
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
	src/terminate/terminate_background.c \
	src/terminate/terminate_execute.c \
	src/terminate/terminate_line.c \
	src/terminate/terminate_pipe.c \
	src/terminate/terminate_redirect.c \
	src/terminate/terminate_sequence.c \
	src/utils.c \
	src/minishell.c
HEADS = \
	include/ft.h \
	include/lexer.h \
	include/parser.h \
	include/run.h \
	include/minishell.h
OBJS = $(SRCS:.c=.o)

CC = cc
INCLUDES = -I./include
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g $(INCLUDES)
LDFLAGS = -lreadline -fsanitize=address

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

run: all
	@./$(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

valgrind: CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)
valgrind: LDFLAGS = -lreadline
valgrind: re
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		./$(NAME)

# vim: ts=4 sts=4 sw=4 noet
