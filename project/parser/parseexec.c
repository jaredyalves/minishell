#include "../lexer/lexer.h"
#include "../minishell.h"
#include "parser.h"

t_cmd	*parseexec(char **ps, char *es)
{
	char		*q;
	char		*eq;
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parseredir(ret, ps, es);
	while (!peek(ps, es, "|)&;"))
	{
		if (get_token(ps, es, &q, &eq) == 0)
			break ;
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc >= MAXARGS)
			panic("minishell: too many args");
		ret = parseredir(ret, ps, es);
	}
	return (ret);
}

// vim: ts=4 sts=4 sw=4 noet
