#include "libft.h"
#include "minishell.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	error_message(char *name, const int status)
{
	if (status == 127)
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", name);
	else if (status == 126)
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", name, strerror(errno));
}

int	execute_external(t_sh *ms, t_execute *cmd)
{
	char	*name;
	int		status;

	name = cmd->argv[0];
	if (name == NULL || *name == '\0')
		return (ms->exit_status);
	if (ft_strchr(name, '/'))
	{
		status = 127;
		if (access(name, F_OK) == 0)
		{
			if (access(name, X_OK) == 0)
				execve(name, cmd->argv, ms->env);
			status = 126;
		}
	}
	else
		status = execute_path(name, cmd->argv, ms->env);
	error_message(name, status);
	return (status);
}
