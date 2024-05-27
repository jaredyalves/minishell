#include "minishell.h"

int runcmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return (-1);
	if (cmd->type == TYPE_EXECUTE)
		return (runexec((t_execcmd *)cmd));
	else if (cmd->type == TYPE_REDIRECT)
		return (runredi((t_redicmd *)cmd));
	else if (cmd->type == TYPE_PIPE)
		return (runpipe((t_pipecmd *)cmd));
	else if (cmd->type == TYPE_SEQUENCE)
		return (runlist((t_listcmd *)cmd));
	else if (cmd->type == TYPE_BACKGROUND)
		return (runback((t_backcmd *)cmd));
	else if (cmd->type == TYPE_AND)
		return (runand((t_andcmd *)cmd));
	else if (cmd->type == TYPE_OR)
		return (runor((t_orcmd *)cmd));
	return (1);
}
