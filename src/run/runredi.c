#include "minishell.h"

int runredi(t_redicmd *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, 0664) < 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", rcmd->file, strerror(errno));
		return (1);
	}
	return (execute(rcmd->command));
}
