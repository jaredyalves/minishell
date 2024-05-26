#include "minishell.h"

void	free_sequence(t_listcmd *s_command)
{
	if (s_command == NULL)
		return ;
	free_command(s_command->left);
	free_command(s_command->right);
	free(s_command);
}
