#include "minishell.h"

void terminate_and(t_andcmd *acmd)
{
	terminate_command(acmd->left);
	terminate_command(acmd->right);
}
