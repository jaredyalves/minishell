#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define RESET "\033[0m"
# define N_BLACK "\033[30m"
# define N_RED "\033[31m"
# define N_GREEN "\033[32m"
# define N_YELLOW "\033[33m"
# define N_BLUE "\033[34m"
# define N_MAGENTA "\033[35m"
# define N_CYAN "\033[36m"
# define N_WHITE "\033[37m"
# define B_BLACK "\033[1m\033[30m"
# define B_RED "\033[1m\033[31m"
# define B_GREEN "\033[1m\033[32m"
# define B_YELLOW "\033[1m\033[33m"
# define B_BLUE "\033[1m\033[34m"
# define B_MAGENTA "\033[1m\033[35m"
# define B_CYAN "\033[1m\033[36m"
# define B_WHITE "\033[1m\033[37m"

# define BLANKS " \t"
# define TOKENS "<|>()&;"

# define ENV_MAX 1024
# define ARG_MAX 1024

typedef enum e_type
{
	EXECUTE,
	REDIRECTION,
	LIST,
	PIPELINE,
}				t_type;

typedef enum e_subtype
{
	REDIRECT,
	HEREDOC,
	PIPE,
	SEQUENCE,
	BACKGROUND,
	AND_IF,
	OR_IF,
}				t_subtype;

typedef struct s_cmd
{
	t_type		type;
}				t_cmd;

typedef struct s_execute
{
	int			type;
	char		*argv[ARG_MAX];
}				t_execute;

typedef struct s_redirection
{
	t_type		type;
	t_subtype	subtype;
	t_cmd		*cmd;
	char		*buffer;
	int			mode;
	int			fd;
}				t_redirection;

typedef struct s_list
{
	t_type		type;
	t_subtype	subtype;
	t_cmd		*left;
	t_cmd		*right;
}				t_list;

typedef struct s_pipeline
{
	t_type		type;
	t_subtype	subtype;
	t_cmd		*left;
	t_cmd		*right;
}				t_pipeline;

typedef struct s_sh
{
	int			init;
	char		*env[ENV_MAX];
	int			keep_running;
	char		*str;
	t_cmd		*cmd;
	int			exit_status;
	int			wait_status;
}				t_sh;

// parse
t_cmd			*execute(void);
t_cmd			*redirection(t_subtype subtype, t_cmd *subcmd, int mode, int fd);
t_cmd			*list(t_subtype subtype, t_cmd *left, t_cmd *right);
t_cmd			*pipeline(t_subtype subtype, t_cmd *left, t_cmd *right);
t_cmd			*parse_command(char *s);
t_cmd			*parse_list1(char **ps, char *es);
t_cmd			*parse_list2(char **ps, char *es);
t_cmd			*parse_pipeline(char **ps, char *es);
t_cmd			*parse_execute(char **ps, char *es);
t_cmd			*parse_block(char **ps, char *es);
t_cmd			*parse_redirection(t_cmd *cmd, char **ps, char *es);
char			*expand_argument(char *q, char *eq);
int				get_token(char **ps, char *es, char **q, char **eq);
int				peek(char **ps, char *es, char *s_tokens, char *d_tokens);

// minishell
t_sh			*get_sh(void);
void			sh_init(int argc, char *argv[], char *envp[]);
void			sh_deinit(void);
int				sh_keep_running(void);

// utils
void			panic(char *error) __attribute__((noreturn));
int				syntax(char **ps, char *es, int allow_block, int allow_newline);
int				fork1(void);
int				get_str(void);
int				pipe1(int *pipes);
t_cmd			*free_command(t_cmd **cmd);
void			handle_signals(void);

#endif
