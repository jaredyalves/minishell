#include "minishell.h"

t_cmd	*execute_command(void)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_EXECUTE;
	cmd->argc = 0;
	return ((t_cmd *)cmd);
}
