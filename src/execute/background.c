#include "minishell.h"

int	execute_background(t_ms *ms, t_backcmd *cmd)
{
	if (cmd->command && fork1() == 0)
		return (execute(ms, cmd->command));
	return (-1);
}
