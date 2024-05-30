#include "minishell.h"

void terminate_execute(t_execcmd *ecmd)
{
	int i;

	i = 0;
	while (i < ecmd->argc)
		*ecmd->eargv[i++] = '\0';
}
