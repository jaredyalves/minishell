#include "minishell.h"

void	free_redirect(t_redicmd *r_command)
{
	if (r_command == NULL)
		return ;
	free_command(r_command->cmd);
	free(r_command);
}
