#include "../lexer/lexer.h"
#include "../minishell.h"
#include "run.h"
#include <sys/wait.h>

void	runlist(t_listcmd *lcmd)
{
	if (fork1() == 0)
		runcmd(lcmd->left);
	wait(0);
	runcmd(lcmd->right);
}

// vim: ts=4 sts=4 sw=4 noet
