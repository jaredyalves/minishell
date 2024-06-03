#include "minishell.h"

int runback(t_backcmd *bcmd)
{
	if (fork1() == 0)
		return (execute(bcmd->command));
	return (0);
}
