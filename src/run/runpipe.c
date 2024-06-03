#include "minishell.h"

int runpipe(t_logicmd *pcmd)
{
	int	p[2];

	if (pipe1(p) == -1)
		return (-1);
	if (fork1() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		return (execute(pcmd->left));
	}
	if (fork() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		return (execute(pcmd->right));
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	return (0);
}
