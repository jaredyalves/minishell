#include "lexer.h"
#include "minishell.h"
#include "run.h"

int runback(t_backcmd *bcmd, char **envp)
{
	if (fork1() == 0)
		return (runcmd(bcmd->cmd, envp));
	return (0);
}

// vim: ts=4 sts=4 sw=4 noet
