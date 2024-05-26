NAME = minishell

SRCS = \
	src/free/free_and.c \
	src/free/free_command.c \
	src/ft/ft_dprintf.c \
	src/ft/ft_memset.c \
	src/ft/ft_split.c \
	src/ft/ft_strcat.c \
	src/ft/ft_strchr.c \
	src/ft/ft_strcpy.c \
	src/ft/ft_strlen.c \
	src/lexer/and_command.c \
	src/lexer/background_command.c \
	src/lexer/execute_command.c \
	src/lexer/or_command.c \
	src/lexer/pipe_command.c \
	src/lexer/redirect_command.c \
	src/lexer/sequence_command.c \
	src/parser/parse_token.c \
	src/parser/parseblock.c \
	src/parser/parsecmd.c \
	src/parser/parseexec.c \
	src/parser/parseline.c \
	src/parser/parsepipe.c \
	src/parser/parseredir.c \
	src/parser/utils.c \
	src/run/runand.c \
	src/run/runback.c \
	src/run/runcmd.c \
	src/run/runexec.c \
	src/run/runlist.c \
	src/run/runor.c \
	src/run/runpipe.c \
	src/run/runredi.c \
	src/terminate/terminate_and.c \
	src/terminate/terminate_background.c \
	src/terminate/terminate_execute.c \
	src/terminate/terminate_line.c \
	src/terminate/terminate_or.c \
	src/terminate/terminate_pipe.c \
	src/terminate/terminate_redirect.c \
	src/terminate/terminate_sequence.c \
	src/utils.c \
    src/free/free_background.c \
    src/free/free_execute.c \
    src/free/free_or.c \
    src/free/free_pipe.c \
    src/free/free_redirect.c \
    src/free/free_sequence.c \
	src/minishell.c
HEADS = include/minishell.h
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
