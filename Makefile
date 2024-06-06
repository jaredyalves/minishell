# Target
NAME := minishell

# Directories
SRCDIR := src
OBJDIR := obj
INCDIR := include

# Files
SRCS := \
	$(SRCDIR)/ft/ft_atoi.c \
	$(SRCDIR)/ft/ft_bzero.c \
	$(SRCDIR)/ft/ft_calloc.c \
	$(SRCDIR)/ft/ft_dprintf.c \
	$(SRCDIR)/ft/ft_getenv.c \
	$(SRCDIR)/ft/ft_isalnum.c \
	$(SRCDIR)/ft/ft_isalpha.c \
	$(SRCDIR)/ft/ft_isascii.c \
	$(SRCDIR)/ft/ft_isdigit.c \
	$(SRCDIR)/ft/ft_isprint.c \
	$(SRCDIR)/ft/ft_itoa.c \
	$(SRCDIR)/ft/ft_memchr.c \
	$(SRCDIR)/ft/ft_memcmp.c \
	$(SRCDIR)/ft/ft_memcpy.c \
	$(SRCDIR)/ft/ft_memmove.c \
	$(SRCDIR)/ft/ft_memset.c \
	$(SRCDIR)/ft/ft_putchar_fd.c \
	$(SRCDIR)/ft/ft_putendl_fd.c \
	$(SRCDIR)/ft/ft_putnbr_fd.c \
	$(SRCDIR)/ft/ft_putstr_fd.c \
	$(SRCDIR)/ft/ft_split.c \
	$(SRCDIR)/ft/ft_strchr.c \
	$(SRCDIR)/ft/ft_strdup.c \
	$(SRCDIR)/ft/ft_striteri.c \
	$(SRCDIR)/ft/ft_strjoin.c \
	$(SRCDIR)/ft/ft_strlcat.c \
	$(SRCDIR)/ft/ft_strlcpy.c \
	$(SRCDIR)/ft/ft_strlen.c \
	$(SRCDIR)/ft/ft_strmapi.c \
	$(SRCDIR)/ft/ft_strncmp.c \
	$(SRCDIR)/ft/ft_strnstr.c \
	$(SRCDIR)/ft/ft_strrchr.c \
	$(SRCDIR)/ft/ft_strtrim.c \
	$(SRCDIR)/ft/ft_substr.c \
	$(SRCDIR)/ft/ft_tolower.c \
	$(SRCDIR)/ft/ft_toupper.c \
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
	$(SRCDIR)/parse/expand.c \
	$(SRCDIR)/utils/fork1.c \
	$(SRCDIR)/utils/free_cmd.c \
	$(SRCDIR)/utils/ms_exit.c \
	$(SRCDIR)/utils/ms_init.c \
	$(SRCDIR)/utils/pipe1.c \
	$(SRCDIR)/utils/signal.c \
	$(SRCDIR)/utils/string.c \
	$(SRCDIR)/utils/terminate.c \
	$(SRCDIR)/main.c
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
INCS := $(INCDIR)/minishell.h $(INCDIR)/ft.h

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
