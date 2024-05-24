#include "minishell.h"

void	freecmd(t_cmd *cmd)
{
	if (cmd->type == TYPE_EXECUTE)
		free(((t_execcmd *)cmd));
	else if (cmd->type == TYPE_REDIRECT)
	{
		freecmd(((t_redicmd *)cmd)->cmd);
		free(((t_redicmd *)cmd));
	}
	else if (cmd->type == TYPE_PIPE)
	{
		freecmd(((t_pipecmd *)cmd)->left);
		freecmd(((t_pipecmd *)cmd)->right);
		free(((t_redicmd *)cmd));
	}
	else if (cmd->type == TYPE_SEQUENCE)
	{
		freecmd(((t_listcmd *)cmd)->left);
		freecmd(((t_listcmd *)cmd)->right);
		free(((t_listcmd *)cmd));
	}
	else if (cmd->type == TYPE_BACKGROUND)
	{
		freecmd(((t_backcmd *)cmd)->cmd);
		free(((t_backcmd *)cmd));
	}
}
