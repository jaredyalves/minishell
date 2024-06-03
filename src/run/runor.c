#include "minishell.h"

int runor(t_logicmd *ocmd)
{
	int status;

	if (fork1() == 0)
		return (execute(ocmd->left));
	waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (execute(ocmd->right));
	return (0);
}
