#include "minishell.h"

void	free_background(t_backcmd *b_command)
{
	if (b_command == NULL)
		return ;
	free_command(b_command->cmd);
	free(b_command);
}
