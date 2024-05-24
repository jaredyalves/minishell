#include "minishell.h"

int runand(t_andcmd *acmd, char **envp)
{
	int status;

	if (fork1() == 0)
		return (runcmd(acmd->left, envp));
	waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (runcmd(acmd->right, envp));
	return (-1);
}
