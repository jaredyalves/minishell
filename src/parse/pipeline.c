#include "minishell.h"

#include <stddef.h>

t_cmd	*parse_pipeline(char **ps, const char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parse_execute(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (peek(ps, es, "|", ""))
	{
		token = get_token(ps, es, NULL, NULL);
		if (peek(ps, es, "<|>&;", "<|>&;"))
			return (free_cmd(&cmd), NULL);
		if (token == '|')
			cmd = logical_command(TYPE_PIPE, cmd, parse_pipeline(ps, es));
	}
	return (cmd);
}
