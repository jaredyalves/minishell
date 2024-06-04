# Target
NAME := minishell

# Directories
SRCDIR := src
OBJDIR := obj
INCDIR := include

# Files
SRCS := \
	$(SRCDIR)/execute/background.c \
	$(SRCDIR)/execute/builtin.c \
	$(SRCDIR)/execute/execute.c \
	$(SRCDIR)/execute/external.c \
	$(SRCDIR)/execute/logical.c \
	$(SRCDIR)/execute/path.c \
	$(SRCDIR)/execute/redirect.c \
	$(SRCDIR)/parse/lexer.c \
	$(SRCDIR)/parse/parse.c \
	$(SRCDIR)/parse/tokenizer.c \
	$(SRCDIR)/utils/command.c \
	$(SRCDIR)/utils/fork_and_pipe.c \
	$(SRCDIR)/utils/ft_dprintf.c \
	$(SRCDIR)/utils/ft_getenv.c \
	$(SRCDIR)/utils/minishell.c \
	$(SRCDIR)/utils/signal.c \
	$(SRCDIR)/utils/string.c \
	$(SRCDIR)/utils/terminate.c \
	$(SRCDIR)/main.c
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
INCS := $(INCDIR)/minishell.h libft/include/libft.h

# Compiler and flags
CC := cc
INCLUDES := -I$(INCDIR) -Ilibft/include
CFLAGS := -Wall -Werror -Wextra -fsanitize=address -g $(INCLUDES)
LDFLAGS := -Llib -lft -lreadline -fsanitize=address

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) lib/libft.a
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

lib/libft.a:
	@mkdir -p $(dir $@)
	make -C libft
	cp libft/libft.a lib

clean:
	make -C libft clean
	rm -rf $(OBJDIR)

fclean: clean
	make -C libft fclean
	rm -f $(NAME) lib/libft.a

re: fclean all
