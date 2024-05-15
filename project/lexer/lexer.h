#ifndef LEXER_H
# define LEXER_H

# define EXEC 1
# define REDI 2
# define PIPE 3
# define LIST 4
# define BACK 5

# define MAXARGS 100

typedef struct s_cmd
{
	int		type;
}			t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}			t_execcmd;

typedef struct s_redicmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}			t_redicmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipecmd;

typedef struct s_listcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_listcmd;

typedef struct s_backcmd
{
	int		type;
	t_cmd	*cmd;
}			t_backcmd;

t_cmd		*execcmd(void);
t_cmd		*redicmd(t_cmd *subcmd, char *file, char *efile, int mode);
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*listcmd(t_cmd *left, t_cmd *right);
t_cmd		*backcmd(t_cmd *subcmd);

#endif

// vim: ts=4 sts=4 sw=4 noet
