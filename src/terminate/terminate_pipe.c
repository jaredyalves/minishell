#include "minishell.h"

void terminate_pipe(t_pipecmd *pcmd)
{
	terminate_line(pcmd->left);
	terminate_line(pcmd->right);
}
