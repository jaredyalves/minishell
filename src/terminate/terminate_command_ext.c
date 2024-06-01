#include "minishell.h"

void	terminate_background(t_backcmd *b_command)
{
	terminate_command(b_command->cmd);
}

void	terminate_and(t_andcmd *a_command)
{
	terminate_command(a_command->left);
	terminate_command(a_command->right);
}

void	terminate_or(t_orcmd *o_command)
{
	terminate_command(o_command->left);
	terminate_command(o_command->right);
}
