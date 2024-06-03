#include "minishell.h"

int runlist(t_logicmd *lcmd)
{
	if (fork1() == 0)
		return (execute(lcmd->left));
	wait(0);
	return (execute(lcmd->right));
}
