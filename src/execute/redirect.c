#include "libft.h"
#include "minishell.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int	execute_redirect(t_sh *ms, t_redicmd *cmd)
{
	close(cmd->fd);
	if (open(cmd->file, cmd->mode, 0664) < 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: ");
		ft_dprintf(STDERR_FILENO, "%s: ", cmd->file);
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
		return (1);
	}
	return (execute_command(ms, cmd->command));
}
