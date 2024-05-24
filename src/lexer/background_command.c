#include "minishell.h"

t_cmd	*background_command(t_cmd *command)
{
	t_backcmd	*cmd;

	cmd = (t_backcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_BACKGROUND;
	cmd->cmd = command;
	return ((t_cmd *)cmd);
}
