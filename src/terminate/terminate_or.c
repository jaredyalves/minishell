#include "minishell.h"

void terminate_or(t_orcmd *ocmd)
{
	terminate_command(ocmd->left);
	terminate_command(ocmd->right);
}
