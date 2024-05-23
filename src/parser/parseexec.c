#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "run.h"

t_cmd	*parseexec(char **ps, char *es)
{
	char		*q;
	char		*eq;
	int			tok;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	while (!peek(ps, es, SYMBOLS))
	{
		tok = get_token(ps, es, &q, &eq);
		if (tok == 0)
			break ;
		if (tok != 'a')
		{
			freecmd(ret);
			panic("minishell: syntax error");
		}
		if (cmd->argc >= ARG_MAX)
		{
			freecmd(ret);
			panic("minishell: too many args");
		}
		cmd->argv[cmd->argc] = q;
		cmd->eargv[cmd->argc] = eq;
		cmd->argc++;
		ret = parseredir(ret, ps, es);
	}
	return (ret);
}

// vim: ts=4 sts=4 sw=4 noet
