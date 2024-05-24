#include "minishell.h"

t_cmd	*backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = (t_backcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_BACKGROUND;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}
