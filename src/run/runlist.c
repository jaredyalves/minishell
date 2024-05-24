#include "minishell.h"

int runlist(t_listcmd *lcmd, char **envp)
{
	if (fork1() == 0)
		return (runcmd(lcmd->left, envp));
	wait(0);
	return (runcmd(lcmd->right, envp));
}
