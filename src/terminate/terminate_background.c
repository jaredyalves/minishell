#include "minishell.h"

void terminate_background(t_backcmd *bcmd)
{
	terminate_command(bcmd->cmd);
}
