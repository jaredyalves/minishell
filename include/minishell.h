#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BOLD_BLACK "\033[1m\033[30m"
# define BOLD_RED "\033[1m\033[31m"
# define BOLD_GREEN "\033[1m\033[32m"
# define BOLD_YELLOW "\033[1m\033[33m"
# define BOLD_BLUE "\033[1m\033[34m"
# define BOLD_MAGENTA "\033[1m\033[35m"
# define BOLD_CYAN "\033[1m\033[36m"
# define BOLD_WHITE "\033[1m\033[37m"

# define WHITESPACE " \t"
# define SYMBOLS "<|>()&;"

# define ENV_MAX 1024

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

typedef struct s_sh
{
	int		init;
	char	*env[ENV_MAX];
	int		keep_running;
	char	*str;
	t_cmd	*cmd;
	int		exit_status;
	int		wait_status;
}			t_sh;

int			execute(t_sh *ms, t_cmd *cmd);
int			is_builtin(t_sh *ms, t_execcmd *cmd);
int			execute_builtin(t_sh *ms, t_execcmd *cmd);
int			execute_external(t_sh *ms, t_execcmd *cmd);
int			execute_andif(t_sh *ms, t_logicmd *cmd);
int			execute_background(t_sh *ms, t_backcmd *cmd);
int			execute_sequence(t_sh *ms, t_logicmd *cmd);
int			execute_orif(t_sh *ms, t_logicmd *cmd);
int			execute_pipe(t_sh *ms, t_logicmd *cmd);
int			execute_redirect(t_sh *ms, t_redicmd *cmd);
int			execute_logical(t_sh *ms, t_logicmd *cmd);
int			execute_heredoc(t_sh *ms, t_herecmd *cmd);

t_cmd		*execute_command(void);
t_cmd		*redirect_command(t_cmd *sub, char *file, char *end_file, int mode);
t_cmd		*heredoc_command(t_cmd *sub);
t_cmd		*background_command(t_cmd *sub);
t_cmd		*logical_command(t_type type, t_cmd *left, t_cmd *right);

t_cmd		*parse_command(char *s);
t_cmd		*parse_list(char **ps, const char *es);
t_cmd		*parse_pipeline(char **ps, const char *es);
t_cmd		*parse_execute(char **ps, const char *es);
t_cmd		*parse_block(char **ps, const char *es);
t_cmd		*parse_redirection(t_cmd *cmd, char **ps, const char *es);
char		**expand_arguments(char **args, char **envp);

int			get_token(char **ps, const char *es, char **q, char **eq);
int peek(char **ps, const char *es, const char *stoks, const char *dtoks);

int			execute_path(const char *name, char **argv, char **envp);
int			fork1(void);
int			pipe1(int *pipes);
void		free_cmd(t_cmd **cmd);
void		terminate(t_cmd *cmd);
void		handle_signals(void);

// minishell
t_sh		*get_sh(void);
void		sh_init(int argc, char *argv[], char *envp[]);
void		sh_deinit(void);
int			sh_keep_running(void);

// utils
void panic(char *error) __attribute__((noreturn));
int  get_str(void);

#endif
