#include "lexer.h"

void	nulexec(t_execcmd *ecmd)
{
	int	i;

	i = 0;
	while (ecmd->argv[i])
		*ecmd->eargv[i++] = 0;
}

// vim: ts=4 sts=4 sw=4 noet
