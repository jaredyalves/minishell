#include "minishell.h"

int runor(t_orcmd *ocmd)
{
	int status;

	if (fork1() == 0)
		return (runcmd(ocmd->left));
	waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (runcmd(ocmd->right));
	return (0);
}
