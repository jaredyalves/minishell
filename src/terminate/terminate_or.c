#include "minishell.h"

void terminate_or(t_orcmd *ocmd)
{
	terminate_line(ocmd->left);
	terminate_line(ocmd->right);
}
