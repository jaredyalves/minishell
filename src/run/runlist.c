#include "minishell.h"

int runlist(t_listcmd *lcmd)
{
	if (fork1() == 0)
		return (runcmd(lcmd->left));
	wait(0);
	return (runcmd(lcmd->right));
}
