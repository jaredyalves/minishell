#include "minishell.h"

void	free_pipe(t_pipecmd *p_command)
{
	if (p_command == NULL)
		return ;
	free_command(p_command->left);
	free_command(p_command->right);
	free(p_command);
}
