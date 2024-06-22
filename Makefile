# Target
NAME := minishell

# Directories
SRCDIR := src
OBJDIR := obj
INCDIR := include

# Files
SRCS := \
	$(SRCDIR)/builtins/ft_cd.c \
	$(SRCDIR)/builtins/ft_echo.c \
	$(SRCDIR)/builtins/ft_env.c \
	$(SRCDIR)/builtins/ft_exit.c \
	$(SRCDIR)/builtins/ft_export.c \
	$(SRCDIR)/builtins/ft_export_ext.c \
	$(SRCDIR)/builtins/ft_pwd.c \
	$(SRCDIR)/builtins/ft_unset.c \
	$(SRCDIR)/execute/builtin.c \
	$(SRCDIR)/execute/command.c \
	$(SRCDIR)/execute/execute.c \
	$(SRCDIR)/execute/external.c \
	$(SRCDIR)/execute/heredoc.c \
	$(SRCDIR)/execute/list.c \
	$(SRCDIR)/execute/pipeline.c \
	$(SRCDIR)/execute/redirection.c \
	$(SRCDIR)/ft/ft_atoi.c \
	$(SRCDIR)/ft/ft_bzero.c \
	$(SRCDIR)/ft/ft_calloc.c \
	$(SRCDIR)/ft/ft_getenv.c \
	$(SRCDIR)/ft/ft_isalnum.c \
	$(SRCDIR)/ft/ft_isalpha.c \
	$(SRCDIR)/ft/ft_isdigit.c \
	$(SRCDIR)/ft/ft_itoa.c \
	$(SRCDIR)/ft/ft_memcpy.c \
	$(SRCDIR)/ft/ft_putchar_fd.c \
	$(SRCDIR)/ft/ft_putstr_fd.c \
	$(SRCDIR)/ft/ft_strchr.c \
	$(SRCDIR)/ft/ft_strdup.c \
	$(SRCDIR)/ft/ft_strjoin.c \
	$(SRCDIR)/ft/ft_strlcat.c \
	$(SRCDIR)/ft/ft_strlcpy.c \
	$(SRCDIR)/ft/ft_strlen.c \
	$(SRCDIR)/ft/ft_strncmp.c \
	$(SRCDIR)/parse/block.c \
	$(SRCDIR)/parse/command.c \
	$(SRCDIR)/parse/execute.c \
	$(SRCDIR)/parse/expand.c \
	$(SRCDIR)/parse/expand_ext.c \
	$(SRCDIR)/parse/lexer.c \
	$(SRCDIR)/parse/list.c \
	$(SRCDIR)/parse/pipeline.c \
	$(SRCDIR)/parse/redirection.c \
	$(SRCDIR)/parse/token.c \
	$(SRCDIR)/utils/command.c \
	$(SRCDIR)/utils/error.c \
	$(SRCDIR)/utils/fork.c \
	$(SRCDIR)/utils/pipe.c \
	$(SRCDIR)/utils/readline.c \
	$(SRCDIR)/utils/signal.c \
	$(SRCDIR)/minishell.c \
	$(SRCDIR)/main.c
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
INCS := $(INCDIR)/minishell.h

# Compiler and flags
CC := cc
INCLUDES := -I$(INCDIR)
CFLAGS := -Wall -Werror -Wextra -g $(INCLUDES)
LDFLAGS := -lreadline

# Targets
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
