#include "minishell.h"

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;
	t_token token;

	cmd = parsepipe(ps, es);
	if (peek(ps, es, "&"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (token == TOKEN_SINGLE_AMPERSAND)
			cmd = background_command(cmd);
		else if (token == TOKEN_DOUBLE_AMPERSAND)
			cmd = and_command(cmd, parseline(ps, es));
	}
	if (peek(ps, es, ";"))
	{
		get_token(ps, es, NULL, NULL);
		cmd = sequence_command(cmd, parseline(ps, es));
	}
	return (cmd);
}
