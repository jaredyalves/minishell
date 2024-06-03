#include "minishell.h"

int runand(t_logicmd *acmd)
{
	int status;

	if (fork1() == 0)
		return (execute(acmd->left));
	waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (execute(acmd->right));
	return (0);
}
