#include "minishell.h"

void	free_and(t_andcmd *a_command)
{
	if (a_command == NULL)
		return ;
	free_command(a_command->left);
	free_command(a_command->right);
	free(a_command);
}
