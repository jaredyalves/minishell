#include "minishell.h"

t_cmd	*parse_pipeline(char **ps, char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parse_execute(ps, es);
	if (!cmd)
		return (0);
	if (peek(ps, es, "|", ""))
	{
		token = get_token(ps, es, 0, 0);
		if (!check_syntax(ps, es, 1, 0))
			return (free_command(&cmd));
		if (token == '|')
			cmd = pipeline(PIPE, cmd, parse_pipeline(ps, es));
		if (!((t_pipeline *)cmd)->right)
			return (free_command(&cmd));
	}
	return (cmd);
}
