#include "minishell.h"

int runback(t_backcmd *bcmd)
{
	if (fork1() == 0)
		return (runcmd(bcmd->cmd));
	return (0);
}
