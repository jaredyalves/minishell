#include "../lexer/lexer.h"
#include "../minishell.h"
#include "run.h"
#include <sys/wait.h>

void	runlist(t_listcmd *lcmd, char **envp)
{
	if (fork1() == 0)
		runcmd(lcmd->left, envp);
	wait(0);
	runcmd(lcmd->right, envp);
}

// vim: ts=4 sts=4 sw=4 noet
