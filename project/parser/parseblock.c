#include "../lexer/lexer.h"
#include "../minishell.h"
#include "parser.h"
#include "run/run.h"

t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		panic("minishell: missing (");
	get_token(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
	{
		freecmd(cmd);
		panic("minishell: missing )");
	}
	get_token(ps, es, 0, 0);
	cmd = parseredir(cmd, ps, es);
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
