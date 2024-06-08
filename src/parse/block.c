#include "minishell.h"

t_cmd	*parse_block(char **ps, const char *es)
{
	t_cmd	*cmd;

	get_token(ps, es, NULL, NULL);
	cmd = parse_list(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (!peek(ps, es, ")", ")"))
		return (free_cmd(&cmd), NULL);
	get_token(ps, es, NULL, NULL);
	cmd = parse_redirection(cmd, ps, es);
	return (cmd);
}
