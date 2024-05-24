#include "minishell.h"

int runback(t_backcmd *bcmd, char **envp)
{
	if (fork1() == 0)
		return (runcmd(bcmd->cmd, envp));
	return (0);
}
