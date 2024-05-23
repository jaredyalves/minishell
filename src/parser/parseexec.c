#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "run.h"

t_cmd	*parseexec(char **ps, char *es)
{
	char		*q;
	char		*eq;
	int			tok;
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
		tok = get_token(ps, es, &q, &eq);
		if (tok == 0)
			break ;
		if (tok != 'a')
		{
			freecmd(ret);
			panic("minishell: syntax error");
		}
		if (argc >= MAXARGS)
		{
			freecmd(ret);
			panic("minishell: too many args");
		}
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		ret = parseredir(ret, ps, es);
	}
	return (ret);
}

// vim: ts=4 sts=4 sw=4 noet
