#include "lexer.h"
#include "parser.h"
#include <stddef.h>

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;
	t_token token;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (token == TOKEN_SINGLE_PIPE)
			cmd = pipecmd(cmd, parsepipe(ps, es));
		else if (token == TOKEN_DOUBLE_PIPE)
			cmd = orcmd(cmd, parseline(ps, es));
	}
	return (cmd);
}
