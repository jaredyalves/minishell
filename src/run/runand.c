#include "minishell.h"

int runand(t_andcmd *acmd)
{
	int status;

	if (fork1() == 0)
		return (runcmd(acmd->left));
	waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (runcmd(acmd->right));
	return (0);
}
