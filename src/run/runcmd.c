#include "minishell.h"

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
	else if (cmd->type == TYPE_AND)
		return (runand((t_andcmd *)cmd, envp));
	else if (cmd->type == TYPE_OR)
		return (runor((t_orcmd *)cmd, envp));
	return (1);
}
