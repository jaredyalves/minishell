#include "../lexer/lexer.h"
#include "../minishell.h"
#include "run.h"
#include <stdlib.h>

void	runcmd(t_cmd *cmd, char **envp)
{
	if (cmd == 0)
		panic("minishell: runcmd error");
	if (cmd->type == EXEC)
		runexec((t_execcmd *)cmd, envp);
	else if (cmd->type == REDI)
		runredi((t_redicmd *)cmd, envp);
	else if (cmd->type == PIPE)
		runpipe((t_pipecmd *)cmd, envp);
	else if (cmd->type == LIST)
		runlist((t_listcmd *)cmd, envp);
	else if (cmd->type == BACK)
		runback((t_backcmd *)cmd, envp);
	freecmd(cmd);
	exit(EXIT_SUCCESS);
}

// vim: ts=4 sts=4 sw=4 noet
