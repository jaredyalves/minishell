#include "lexer.h"
#include "run.h"
#include <stddef.h>

int runcmd(t_cmd *cmd, char **envp)
{
	if (cmd == NULL)
		return (-1);
	if (cmd->type == TYPE_EXECUTE)
		return (runexec((t_execcmd *)cmd, envp));
	else if (cmd->type == TYPE_REDIRECT)
		return (runredi((t_redicmd *)cmd, envp));
	else if (cmd->type == TYPE_PIPE)
		return (runpipe((t_pipecmd *)cmd, envp));
	else if (cmd->type == TYPE_SEQUENCE)
		return (runlist((t_listcmd *)cmd, envp));
	else if (cmd->type == TYPE_BACKGROUND)
		return (runback((t_backcmd *)cmd, envp));
	return (0);
}

// vim: ts=4 sts=4 sw=4 noet
