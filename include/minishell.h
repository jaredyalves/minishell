#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft.h"

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef enum e_type
{
	TYPE_EXECUTE,
	TYPE_REDIRECT,
	TYPE_PIPE,
	TYPE_SEQUENCE,
	TYPE_BACKGROUND,
	TYPE_AND,
	TYPE_OR,
	TYPE_LOGICAL,
}			t_type;

typedef enum e_token
{
	TOKEN_LEFT_PARENTHESES,
	TOKEN_RIGHT_PARENTHESES,
	TOKEN_DOUBLE_AMPERSAND,
	TOKEN_SINGLE_AMPERSAND,
	TOKEN_DOUBLE_GREATER,
	TOKEN_SINGLE_GREATER,
	TOKEN_DOUBLE_LESS,
	TOKEN_SINGLE_LESS,
	TOKEN_DOUBLE_PIPE,
	TOKEN_SINGLE_PIPE,
	TOKEN_SINGLE_SEMICOLON,
	TOKEN_QUOTE,
	TOKEN_WORD,
	TOKEN_NULL,
}			t_token;

typedef struct s_cmd
{
	t_type	type;
}			t_cmd;

typedef struct s_execcmd
{
	t_type	type;
	int		argc;
	char	*argv[ARG_MAX];
	char	*end_argv[ARG_MAX];
}			t_execcmd;

typedef struct s_redicmd
{
	t_type	type;
	t_cmd	*command;
	char	*file;
	char	*end_file;
	int		mode;
	int		fd;
}			t_redicmd;

typedef struct s_backcmd
{
	t_type	type;
	t_cmd	*command;
}			t_backcmd;

typedef struct s_logicmd
{
	t_type	type;
	t_type	sub;
	t_cmd	*left;
	t_cmd	*right;
}			t_logicmd;

typedef struct s_ms
{
	char	*env[ARG_MAX];
	char	*str;
	t_cmd	*cmd;
	int		exit_status;
	int		wait_status;
}			t_ms;

t_ms		*ms_init(int argc, const char **argv, char **envp);
int			ms_exit(t_ms **ms);

int			execute(t_ms *ms, t_cmd *cmd);
int			is_builtin(t_ms *ms, t_execcmd *cmd);
int			execute_builtin(t_ms *ms, t_execcmd *cmd);
int			execute_external(t_ms *ms, t_execcmd *cmd);
int			execute_andif(t_ms *ms, t_logicmd *cmd);
int			execute_background(t_ms *ms, t_backcmd *cmd);
int			execute_sequence(t_ms *ms, t_logicmd *cmd);
int			execute_orif(t_ms *ms, t_logicmd *cmd);
int			execute_pipe(t_ms *ms, t_logicmd *cmd);
int			execute_redirect(t_ms *ms, t_redicmd *cmd);

t_cmd		*execute_command(void);
t_cmd		*redirect_command(t_cmd *sub, char *file, char *end_file, int mode);
t_cmd		*background_command(t_cmd *sub);
t_cmd		*logical_command(t_type type, t_cmd *left, t_cmd *right);

t_cmd		*parse(char *str);
t_cmd		*parse_list(char **ps, const char *es);
t_cmd		*parse_pipeline(char **ps, const char *es);
t_cmd		*parse_command(char **ps, const char *es);
t_cmd		*parse_block(char **ps, const char *es);
t_cmd		*parse_redirection(t_cmd *command, char **ps, const char *es);
int			find_token(char **ps, const char *s, const t_token *to_search);
t_token		get_token(char **ps, const char *es, char **q, char **eq);
t_token		peek_token(char **ps, const char *es, int skip);
char		**expand_arguments(char **args, char **envp);

char		*get_str(char *str);
int			execute_path(const char *name, char **argv, char **envp);
int			fork1(void);
int			pipe1(int *pipes);
void		free_cmd(t_cmd **cmd);
void		free_str(char **str);
void		terminate(t_cmd *cmd);
void		setup_signal_handlers(void);

#endif
