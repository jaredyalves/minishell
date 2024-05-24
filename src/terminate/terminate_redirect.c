#include "minishell.h"

void terminate_redirect(t_redicmd *rcmd)
{
	terminate_line(rcmd->cmd);
	*rcmd->efile = 0;
}
