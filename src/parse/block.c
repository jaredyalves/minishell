#include "minishell.h"

t_cmd	*parse_block(char **ps, char *es)
{
	t_cmd	*cmd;

	get_token(ps, es, 0, 0);
	if (!syntax(ps, es, 0, 0))
		return (0);
	cmd = parse_list1(ps, es);
	if (!cmd)
		return (0);
	if (!peek(ps, es, ")", ")"))
		return (free_command(&cmd));
	get_token(ps, es, 0, 0);
	cmd = parse_redirection(cmd, ps, es);
	return (cmd);
}
