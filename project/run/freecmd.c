#include "../lexer/lexer.h"
#include <stdlib.h>

void	freecmd(t_cmd *cmd)
{
	if (cmd->type == EXEC)
		free(((t_execcmd *)cmd));
	else if (cmd->type == REDI)
	{
		freecmd(((t_redicmd *)cmd)->cmd);
		free(((t_redicmd *)cmd));
	}
	else if (cmd->type == PIPE)
	{
		freecmd(((t_pipecmd *)cmd)->left);
		freecmd(((t_pipecmd *)cmd)->right);
		free(((t_redicmd *)cmd));
	}
	else if (cmd->type == LIST)
	{
		freecmd(((t_listcmd *)cmd)->left);
		freecmd(((t_listcmd *)cmd)->right);
		free(((t_listcmd *)cmd));
	}
	else if (cmd->type == BACK)
	{
		freecmd(((t_backcmd *)cmd)->cmd);
		free(((t_backcmd *)cmd));
	}
}

// vim: ts=4 sts=4 sw=4 noet
