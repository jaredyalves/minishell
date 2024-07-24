NAME		:= minishell

LIBDIR		:= lib
SRCDIR		:= src
OBJDIR		:= obj
INCDIR		:= include

LIBFT_DIR	:= $(LIBDIR)/libft
LIBFT_NAME	:= libft.a
LIBFT		:= $(LIBFT_DIR)/$(LIBFT_NAME)

SRCS		:= \
	$(SRCDIR)/main.c \
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
	$(SRCDIR)/utils/getenv.c \
	$(SRCDIR)/utils/minishell.c \
	$(SRCDIR)/utils/pipe.c \
	$(SRCDIR)/utils/readline.c \
	$(SRCDIR)/utils/signal.c \
	$(SRCDIR)/utils/utils.c \

OBJS		:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
INCS		:= $(INCDIR)/minishell.h

CC			:= cc
INCLUDES	:= -I$(INCDIR) -I$(LIBFT_DIR)/include
CFLAGS		:= -O3 -Wall -Werror -Wextra $(INCLUDES)
LDFLAGS		:= -L$(LIBFT_DIR) -lft -lreadline

RM			:= rm
RMFLAGS		:= -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(RMFLAGS) $(OBJDIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
