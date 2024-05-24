#include "minishell.h"

int runpipe(t_pipecmd *pcmd, char **envp)
{
	int	p[2];

	if (pipe(p) < 0)
		panic("pipe", (t_cmd *)pcmd);
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		return (runcmd(pcmd->left, envp));
	}
	if (fork() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		return (runcmd(pcmd->right, envp));
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	return (0);
}
