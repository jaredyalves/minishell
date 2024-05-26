#include "minishell.h"

void	free_execute(t_execcmd *e_command)
{
	if (e_command == NULL)
		return ;
	free(e_command);
}
