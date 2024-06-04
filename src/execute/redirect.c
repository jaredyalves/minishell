#include "minishell.h"

int	execute_redirect(t_ms *ms, t_redicmd *cmd)
{
	close(cmd->fd);
	if (open(cmd->file, cmd->mode, 0664) < 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: ");
		ft_dprintf(STDERR_FILENO, "%s: ", cmd->file);
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
		return (1);
	}
	return (execute(ms, cmd->command));
}
