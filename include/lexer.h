#ifndef LEXER_H
# define LEXER_H

#include <linux/limits.h>

typedef enum e_type
{
	TYPE_EXECUTE,
	TYPE_REDIRECT,
	TYPE_PIPE,
	TYPE_SEQUENCE,
	TYPE_BACKGROUND,
} t_type;

typedef struct s_cmd
{
	t_type type;
}			t_cmd;

typedef struct s_execcmd
{
	t_type	 type;
	int		 argc;
	char	*argv[ARG_MAX];
	char	*eargv[ARG_MAX];
}			t_execcmd;

typedef struct s_redicmd
{
	t_type	 type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}			t_redicmd;

typedef struct s_pipecmd
{
	t_type	 type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipecmd;

typedef struct s_listcmd
{
	t_type	 type;
	t_cmd	*left;
	t_cmd	*right;
}			t_listcmd;

typedef struct s_backcmd
{
	t_type type;
	t_cmd	*cmd;
}			t_backcmd;

t_cmd		*execcmd(void);
t_cmd		*redicmd(t_cmd *subcmd, char *file, char *efile, int mode);
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*listcmd(t_cmd *left, t_cmd *right);
t_cmd		*backcmd(t_cmd *subcmd);

#endif

// vim: ts=4 sts=4 sw=4 noet
