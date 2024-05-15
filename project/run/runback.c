#include "../lexer/lexer.h"
#include "../minishell.h"
#include "run.h"

void	runback(t_backcmd *bcmd)
{
	if (fork1() == 0)
		runcmd(bcmd->cmd);
}

// vim: ts=4 sts=4 sw=4 noet
