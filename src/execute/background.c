#include "minishell.h"

int	execute_background(t_sh *ms, t_backcmd *cmd)
{
	if (cmd->command && fork1() == 0)
		execute(ms, cmd->command);
	return (0);
}
