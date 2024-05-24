#include "lexer.h"
#include "parser.h"
#include <stddef.h>

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;
	t_token token;

	cmd = parsepipe(ps, es);
	if (peek(ps, es, "&"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (token == TOKEN_SINGLE_AMPERSAND)
			cmd = backcmd(cmd);
		else if (token == TOKEN_DOUBLE_AMPERSAND)
			cmd = andcmd(cmd, parseline(ps, es));
	}
	if (peek(ps, es, ";"))
	{
		get_token(ps, es, NULL, NULL);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return (cmd);
}
