#include "minishell.h"

void	free_command(t_cmd *command)
{
	if (command == NULL)
		return ;
	if (command->type == TYPE_EXECUTE)
		free_execute((t_execcmd *)command);
	else if (command->type == TYPE_REDIRECT)
		free_redirect((t_redicmd *)command);
	else if (command->type == TYPE_PIPE)
		free_pipe((t_pipecmd *)command);
	else if (command->type == TYPE_SEQUENCE)
		free_sequence((t_listcmd *)command);
	else if (command->type == TYPE_BACKGROUND)
		free_background((t_backcmd *)command);
	else if (command->type == TYPE_AND)
		free_and((t_andcmd *)command);
	else if (command->type == TYPE_OR)
		free_or((t_orcmd *)command);
}
