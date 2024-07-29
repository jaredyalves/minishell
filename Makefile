NAME			:=	minishell
NAME_BONUS		:=

SRCDIR			:=	src
OBJDIR			:=	obj
LIBDIR			:=	lib
INCDIR			:=	include

LIBFT_DIR		:=	$(LIBDIR)/libft
LIBFT_NAME		:=	libft.a
LIBFT			:=	$(LIBFT_DIR)/$(LIBFT_NAME)

GNL_DIR			:=	$(LIBDIR)/get_next_line
GNL_NAME		:=	libgnl.a
GNL				:=	$(GNL_DIR)/$(GNL_NAME)

SRCS			:=	$(SRCDIR)/main.c
SRCS			+=	$(SRCDIR)/builtins/ft_cd.c
SRCS			+=	$(SRCDIR)/builtins/ft_echo.c
SRCS			+=	$(SRCDIR)/builtins/ft_env.c
SRCS			+=	$(SRCDIR)/builtins/ft_exit.c
SRCS			+=	$(SRCDIR)/builtins/ft_export.c
SRCS			+=	$(SRCDIR)/builtins/ft_export_ext.c
SRCS			+=	$(SRCDIR)/builtins/ft_pwd.c
SRCS			+=	$(SRCDIR)/builtins/ft_unset.c
SRCS			+=	$(SRCDIR)/execute/builtin.c
SRCS			+=	$(SRCDIR)/execute/command.c
SRCS			+=	$(SRCDIR)/execute/execute.c
SRCS			+=	$(SRCDIR)/execute/external.c
SRCS			+=	$(SRCDIR)/execute/list.c
SRCS			+=	$(SRCDIR)/execute/pipeline.c
SRCS			+=	$(SRCDIR)/execute/redirection.c
SRCS			+=	$(SRCDIR)/parse/block.c
SRCS			+=	$(SRCDIR)/parse/command.c
SRCS			+=	$(SRCDIR)/parse/execute.c
SRCS			+=	$(SRCDIR)/parse/expand.c
SRCS			+=	$(SRCDIR)/parse/expand_ext.c
SRCS			+=	$(SRCDIR)/parse/heredoc.c
SRCS			+=	$(SRCDIR)/parse/heredoc_ext.c
SRCS			+=	$(SRCDIR)/parse/lexer.c
SRCS			+=	$(SRCDIR)/parse/list.c
SRCS			+=	$(SRCDIR)/parse/pipeline.c
SRCS			+=	$(SRCDIR)/parse/redirection.c
SRCS			+=	$(SRCDIR)/parse/token.c
SRCS			+=	$(SRCDIR)/utils/command.c
SRCS			+=	$(SRCDIR)/utils/error.c
SRCS			+=	$(SRCDIR)/utils/fork.c
SRCS			+=	$(SRCDIR)/utils/getenv.c
SRCS			+=	$(SRCDIR)/utils/minishell.c
SRCS			+=	$(SRCDIR)/utils/pipe.c
SRCS			+=	$(SRCDIR)/utils/readline.c
SRCS			+=	$(SRCDIR)/utils/signal.c
SRCS			+=	$(SRCDIR)/utils/utils.c
SRCS_BONUS		:=
OBJS			:=	$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
OBJS_BONUS		:=	$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS_BONUS))
INCS			:=	$(INCDIR)/minishell.h
INCS_BONUS		:=

CC				:=	/bin/cc
INCLUDES		:=	-I$(INCDIR) -I$(LIBFT_DIR)/include -I$(GNL_DIR)/include
CFLAGS			:=	-O3 -Wall -Werror -Wextra $(INCLUDES)
LDFLAGS			:=	-lreadline -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl

AR				:=	/bin/ar
ARFLAGS			:=	-rcs

RM				:=	/bin/rm
RMFLAGS			:=	-rf

COLOR_RESET		:=	\033[0m
COLOR_CLEAN		:=	\033[0;33m
COLOR_COMPILE	:=	\033[0;32m
COLOR_LINK		:=	\033[0;34m

.PHONY: all bonus clean fclean re

all: $(NAME)

# bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	@printf "$(COLOR_LINK)Linking $@...$(COLOR_RESET)\n"
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(LIBFT):
	@printf "$(COLOR_COMPILE)Building $(LIBFT_NAME)...$(COLOR_RESET)\n"
	@make -C $(LIBFT_DIR)

$(GNL):
	@printf "$(COLOR_COMPILE)Building $(GNL_NAME)...$(COLOR_RESET)\n"
	@make -C $(GNL_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	@printf "$(COLOR_COMPILE)Compiling $<...$(COLOR_RESET)\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@printf "$(COLOR_CLEAN)Cleaning up...$(COLOR_RESET)\n"
	@$(RM) $(RMFLAGS) $(OBJDIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(GNL_DIR) clean

fclean: clean
	@printf "$(COLOR_CLEAN)Removing $(NAME)...$(COLOR_RESET)\n"
	@$(RM) $(RMFLAGS) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(GNL_DIR) fclean

re: fclean all
