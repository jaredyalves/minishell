#include "lexer.h"
#include "parser.h"
#include <stddef.h>

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
	if (peek(ps, es, "&"))
	{
		get_token(ps, es, NULL, NULL);
		cmd = backcmd(cmd);
	}
	if (peek(ps, es, ";"))
	{
		get_token(ps, es, NULL, NULL);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
