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

#define WHITESPACE " \t\r\n\v"
#define SYMBOLS "<|>&;()"

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
	TOKEN_NULL,
	TOKEN_NO_SPECIAL,
	TOKEN_SINGLE_AMPERSAND,
	TOKEN_DOUBLE_AMPERSAND,
	TOKEN_SINGLE_PIPE,
	TOKEN_DOUBLE_PIPE,
	TOKEN_SINGLE_LESS,
	TOKEN_DOUBLE_LESS,
	TOKEN_SINGLE_GREATER,
	TOKEN_DOUBLE_GREATER,
	TOKEN_SINGLE_SEMICOLON,
	TOKEN_LEFT_PARENTHESES,
	TOKEN_RIGHT_PARENTHESES,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
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

// Lexer
t_cmd *and_command(t_cmd *left, t_cmd *right);
t_cmd *background_command(t_cmd *command);
t_cmd *execute_command(void);
t_cmd *or_command(t_cmd *left, t_cmd *right);
t_cmd *pipe_command(t_cmd *left, t_cmd *right);
t_cmd *redirect_command(t_cmd *command, char *file, char *end_file, int mode);
t_cmd *sequence_command(t_cmd *left, t_cmd *right);

// Parser
int		peek(char **ps, char *es, char *tokens);
t_cmd  *parseblock(char **ps, char *es);
t_cmd  *parsecmd(char *s);
t_cmd  *parseexec(char **ps, char *es);
t_cmd  *parseline(char **ps, char *es);
t_cmd  *parsepipe(char **ps, char *es);
t_cmd  *parseredir(t_cmd *cmd, char **ps, char *es);
t_token get_token(char **ps, char *es, char **q, char **eq);
t_token parse_token(char **ps, const char *es);

// Run
int runand(t_andcmd *acmd, char **envp);
int runback(t_backcmd *bcmd, char **envp);
int runcmd(t_cmd *cmd, char **envp);
int runexec(t_execcmd *ecmd, char **envp);
int runlist(t_listcmd *lcmd, char **envp);
int runor(t_orcmd *ocmd, char **envp);
int runpipe(t_pipecmd *pcmd, char **envp);
int runredi(t_redicmd *rcmd, char **envp);

// Terminate
void   terminate_execute(t_execcmd *ecmd);
void   terminate_redirect(t_redicmd *rcmd);
void   terminate_pipe(t_pipecmd *pcmd);
void   terminate_sequence(t_listcmd *lcmd);
void   terminate_background(t_backcmd *bcmd);
void   terminate_and(t_andcmd *acmd);
void   terminate_or(t_orcmd *ocmd);
t_cmd *terminate_line(t_cmd *cmd);

// Utils
char   *get_line(char *line);
void	panic(char *str, t_cmd *cmd);
int		fork1(void);
void	freecmd(t_cmd *cmd);

// Ft
char  *ft_strchr(const char *s, int c);
char **ft_split(char *str, char chr);
size_t ft_dprintf(int fd, const char *format, ...);
size_t ft_strlen(const char *s);
void  *ft_memset(void *s, int c, size_t n);

#endif
