#include "minishell.h"

void terminate_pipe(t_pipecmd *pcmd)
{
	terminate_command(pcmd->left);
	terminate_command(pcmd->right);
}
