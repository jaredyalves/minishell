# Target
NAME := minishell

# Directories
SRCDIR := src
OBJDIR := obj
INCDIR := include

# Files
SRCS := \
	$(SRCDIR)/execute/builtin.c \
	$(SRCDIR)/execute/execute.c \
	$(SRCDIR)/execute/external.c \
	$(SRCDIR)/ft/ft_dprintf.c \
	$(SRCDIR)/ft/ft_memset.c \
	$(SRCDIR)/ft/ft_split.c \
	$(SRCDIR)/ft/ft_strcat.c \
	$(SRCDIR)/ft/ft_strchr.c \
	$(SRCDIR)/ft/ft_strcpy.c \
	$(SRCDIR)/ft/ft_strlen.c \
	$(SRCDIR)/ft/ft_strncpy.c \
	$(SRCDIR)/ft/ft_strndup.c \
	$(SRCDIR)/ft/ft_strnlen.c \
	$(SRCDIR)/ft/ft_getenv.c \
	$(SRCDIR)/parse/lexer.c \
	$(SRCDIR)/parse/parse.c \
	$(SRCDIR)/parse/tokenizer.c \
	$(SRCDIR)/run/runand.c \
	$(SRCDIR)/run/runback.c \
	$(SRCDIR)/run/runexec.c \
	$(SRCDIR)/run/runlist.c \
	$(SRCDIR)/run/runor.c \
	$(SRCDIR)/run/runpipe.c \
	$(SRCDIR)/run/runredi.c \
	$(SRCDIR)/utils/fork_and_pipe.c \
	$(SRCDIR)/utils/free_command.c \
	$(SRCDIR)/utils/line.c \
	$(SRCDIR)/utils/null_terminate.c \
	$(SRCDIR)/utils/execute_from_path.c \
	$(SRCDIR)/utils/shell.c \
	$(SRCDIR)/utils/signal.c \
	$(SRCDIR)/main.c
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
INCS := $(INCDIR)/minishell.h

# Compiler and flags
CC := cc
INCLUDES := -I$(INCDIR)
CFLAGS := -Wall -Werror -Wextra -fsanitize=address -g $(INCLUDES)
LDFLAGS := -lreadline -fsanitize=address

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
