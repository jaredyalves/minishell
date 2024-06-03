#ifndef MINISHELL_H
# define MINISHELL_H

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
	t_type	sub_type;
	t_cmd	*left;
	t_cmd	*right;
}			t_logicmd;

typedef struct s_shell
{
	char	*cmdline;
	char	*environ[ARG_MAX];
	int		stop;
	int		status;
	int		exit_status;
	t_cmd	*command;
}			t_shell;

t_shell		*get_shell(void);
void		init_shell(int argc, char **argv, char **envp);
int			cleanup_shell(void);

int			execute(t_cmd *command);
int			execute_builtin(t_execcmd *command);
int			is_builtin(t_execcmd *command);
int			execute_external(t_execcmd *e_command);
int			runand(t_logicmd *acmd);
int			runback(t_backcmd *bcmd);
int			runlist(t_logicmd *lcmd);
int			runor(t_logicmd *ocmd);
int			runpipe(t_logicmd *pcmd);
int			runredi(t_redicmd *rcmd);

t_cmd		*execute_command(void);
t_cmd		*redirect_command(t_cmd *sub, char *file, char *end_file, int mode);
t_cmd		*background_command(t_cmd *sub);
t_cmd		*logical_command(t_type type, t_cmd *left, t_cmd *right);

t_cmd		*parse_cmdline(char *cmdline);
t_cmd		*parse_list(char **ps, const char *es);
t_cmd		*parse_pipeline(char **ps, const char *es);
t_cmd		*parse_command(char **ps, const char *es);
t_cmd		*parse_block(char **ps, const char *es);
t_cmd		*parse_redirection(t_cmd *command, char **ps, const char *es);
int			find_token(char **ps, const char *s, const t_token *to_search);
t_token		get_token(char **ps, const char *es, char **q, char **eq);
t_token		peek_token(char **ps, const char *es, int skip);

char		*get_line(char *line);
int			execute_from_path(const char *name, char **argv, char **envp);
int			fork1(void);
int			pipe1(int *pipes);
void		free_command(t_cmd **p_command);
void		free_line(char **p_line);
void		null_terminate(t_cmd *command);
void		setup_signal_handlers(void);

char		**ft_split(char *str, char chr);
char		*ft_getenv(const char *name);
char		*ft_strcat(char *dst, const char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t n);
char		*ft_strndup(const char *src, size_t n);
size_t		ft_dprintf(int fd, const char *format, ...);
size_t		ft_strlen(const char *s);
size_t		ft_strnlen(const char *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);

#endif
