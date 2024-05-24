#include "minishell.h"

void terminate_execute(t_execcmd *ecmd)
{
	int	i;

	i = 0;
	while (ecmd->argv[i])
		*ecmd->eargv[i++] = 0;
}
