#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITESPACE " \t"
# define SYMBOLS "<|>()&;"

typedef enum e_type
{
	TYPE_EXECUTE,
	TYPE_REDIRECT,
	TYPE_HEREDOC,
	TYPE_PIPE,
	TYPE_SEQUENCE,
	TYPE_BACKGROUND,
	TYPE_AND,
	TYPE_OR,
	TYPE_LOGICAL,
}			t_type;

typedef struct s_cmd
{
	t_type	type;
}			t_cmd;

typedef struct s_execcmd
{
	t_type	type;
	int		argc;
	char	*argv[1024];
	char	*end_argv[1024];
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

typedef struct s_herecmd
{
	t_type	type;
	t_cmd	*command;
	char	buffer[1024];
}			t_herecmd;

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
	char	*env[1024];
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
int			execute_logical(t_ms *ms, t_logicmd *cmd);
int			execute_heredoc(t_ms *ms, t_herecmd *cmd);

t_cmd		*execute_command(void);
t_cmd		*redirect_command(t_cmd *sub, char *file, char *end_file, int mode);
t_cmd		*heredoc_command(t_cmd *sub);
t_cmd		*background_command(t_cmd *sub);
t_cmd		*logical_command(t_type type, t_cmd *left, t_cmd *right);

t_cmd		*parse(char *str);
t_cmd		*parse_list(char **ps, const char *es);
t_cmd		*parse_pipeline(char **ps, const char *es);
t_cmd		*parse_command(char **ps, const char *es);
t_cmd		*parse_block(char **ps, const char *es);
t_cmd		*parse_redirection(t_cmd *cmd, char **ps, const char *es);
char		**expand_arguments(char **args, char **envp);

int			get_token(char **ps, const char *es, char **q, char **eq);
int			peek(char **ps, const char *es, const char *stoks, const char *dtoks);

char		*get_str(const t_ms *ms, char *str);
int			execute_path(const char *name, char **argv, char **envp);
int			fork1(void);
int			pipe1(int *pipes);
void		free_cmd(t_cmd **cmd);
void		free_str(char **str);
void		terminate(t_cmd *cmd);
void		setup_signal_handlers(void);

void		panic(const char *err) __attribute__((noreturn));

#endif
