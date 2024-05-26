#include "minishell.h"

void	free_or(t_orcmd *o_command)
{
	if (o_command == NULL)
		return ;
	free_command(o_command->left);
	free_command(o_command->right);
	free(o_command);
}
