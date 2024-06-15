#ifndef PARSE_H
# define PARSE_H

# include "minishell/limits.h"

# define BLANKS " \t"
# define TOKENS "<|>()&;"

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

t_cmd			*execute(void);
t_cmd			*redirection(t_subtype subtype, t_cmd *subcmd, int mode,
					int fd);
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

#endif
