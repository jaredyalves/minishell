#include "minishell.h"

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;
	t_token token;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (token == TOKEN_SINGLE_PIPE)
			cmd = pipe_command(cmd, parsepipe(ps, es));
		else if (token == TOKEN_DOUBLE_PIPE)
			cmd = or_command(cmd, parseline(ps, es));
	}
	return (cmd);
}
