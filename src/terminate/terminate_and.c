#include "minishell.h"

void terminate_and(t_andcmd *acmd)
{
	terminate_line(acmd->left);
	terminate_line(acmd->right);
}
