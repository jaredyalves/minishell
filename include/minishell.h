#ifndef MINISHELL_H
# define MINISHELL_H

#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef enum e_type
{
	TYPE_EXECUTE,
	TYPE_REDIRECT,
	TYPE_PIPE,
	TYPE_SEQUENCE,
	TYPE_BACKGROUND,
	TYPE_AND,
	TYPE_OR,
} t_type;

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
} t_token;

typedef struct s_cmd
{
	t_type type;
} t_cmd;

typedef struct s_execcmd
{
	t_type type;
	int	   argc;
	char  *argv[ARG_MAX];
	char  *eargv[ARG_MAX];
} t_execcmd;

typedef struct s_redicmd
{
	t_type type;
	t_cmd *cmd;
	char  *file;
	char  *efile;
	int	   mode;
	int	   fd;
} t_redicmd;

typedef struct s_pipecmd
{
	t_type type;
	t_cmd *left;
	t_cmd *right;
} t_pipecmd;

typedef struct s_listcmd
{
	t_type type;
	t_cmd *left;
	t_cmd *right;
} t_listcmd;

typedef struct s_backcmd
{
	t_type type;
	t_cmd *cmd;
} t_backcmd;

typedef struct s_andcmd
{
	t_type type;
	t_cmd *left;
	t_cmd *right;
} t_andcmd;

typedef struct s_orcmd
{
	t_type type;
	t_cmd *left;
	t_cmd *right;
} t_orcmd;

typedef struct s_shell
{
	char  *cmdline;
	char  *environ[ARG_MAX];
} t_shell;

// Shell
t_shell *get_shell(void);

// Lexer
t_cmd *and_command(t_cmd *left, t_cmd *right);
t_cmd *background_command(t_cmd *command);
t_cmd *execute_command(void);
t_cmd *or_command(t_cmd *left, t_cmd *right);
t_cmd *pipe_command(t_cmd *left, t_cmd *right);
t_cmd *redirect_command(t_cmd *command, char *file, char *end_file, int mode);
t_cmd *sequence_command(t_cmd *left, t_cmd *right);

// Parser
t_cmd  *parse_cmdline(char *cmdline);
t_cmd  *parse_list(char **ps, const char *es);
t_cmd  *parse_pipeline(char **ps, const char *es);
t_cmd  *parse_command(char **ps, const char *es);
t_cmd  *parse_block(char **ps, const char *es);
t_cmd  *parse_redirection(t_cmd *command, char **ps, const char *es);
int		find_token(char **ps, const char *s, const t_token *to_search);
t_token get_token(char **ps, const char *es, char **q, char **eq);
t_token peek_token(char **ps, const char *es, int skip);

// Run
int runand(t_andcmd *acmd);
int runback(t_backcmd *bcmd);
int runcmd(t_cmd *cmd);
int runexec(t_execcmd *ecmd);
int runlist(t_listcmd *lcmd);
int runor(t_orcmd *ocmd);
int runpipe(t_pipecmd *pcmd);
int runredi(t_redicmd *rcmd);

// Terminate
void terminate_command(t_cmd *cmd);
void terminate_execute(t_execcmd *e_command);
void terminate_redirect(t_redicmd *r_command);
void terminate_pipe(t_pipecmd *p_command);
void terminate_sequence(t_listcmd *s_command);
void terminate_background(t_backcmd *b_command);
void terminate_and(t_andcmd *a_command);
void terminate_or(t_orcmd *o_command);

// Free
void free_and(t_andcmd *a_command);
void free_background(t_backcmd *b_command);
void free_command(t_cmd *command);
void free_execute(t_execcmd *e_command);
void free_or(t_orcmd *o_command);
void free_pipe(t_pipecmd *p_command);
void free_redirect(t_redicmd *r_command);
void free_sequence(t_listcmd *s_command);

// Utils
char   *get_line(char *line);
void	panic(char *str, t_cmd *cmd);
int		fork1(void);
int		pipe1(int *pipes);

// Ft
char  *ft_strcat(char *dst, const char *src);
char  *ft_strchr(const char *s, int c);
char  *ft_strcpy(char *dst, const char *src);
char  *ft_strncpy(char *dst, const char *src, size_t n);
char  *ft_strndup(const char *src, size_t n);
char **ft_split(char *str, char chr);
size_t ft_dprintf(int fd, const char *format, ...);
size_t ft_strlen(const char *s);
size_t ft_strnlen(const char *s, size_t n);
void  *ft_memset(void *s, int c, size_t n);

#endif
