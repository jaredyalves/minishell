#include "minishell.h"

void terminate_redirect(t_redicmd *rcmd)
{
	terminate_command(rcmd->cmd);
	*rcmd->efile = 0;
}
