#include "lexer.h"
#include "minishell.h"
#include "run.h"
#include <stdlib.h>

void	runcmd(t_cmd *cmd, char **envp)
{
	if (cmd == 0)
		panic("minishell: runcmd error");
	if (cmd->type == TYPE_EXECUTE)
		runexec((t_execcmd *)cmd, envp);
	else if (cmd->type == TYPE_REDIRECT)
		runredi((t_redicmd *)cmd, envp);
	else if (cmd->type == TYPE_PIPE)
		runpipe((t_pipecmd *)cmd, envp);
	else if (cmd->type == TYPE_SEQUENCE)
		runlist((t_listcmd *)cmd, envp);
	else if (cmd->type == TYPE_BACKGROUND)
		runback((t_backcmd *)cmd, envp);
	freecmd(cmd);
	exit(EXIT_SUCCESS);
}

// vim: ts=4 sts=4 sw=4 noet
