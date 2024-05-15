#include "../lexer/lexer.h"
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// FIXME: Can't use fprintf(), replace with a ft function
void	runexec(t_execcmd *ecmd)
{
	if (ecmd->argv[0] == 0)
		panic("minishell: runexec error");
	execve(ecmd->argv[0], ecmd->argv, 0);
	fprintf(stderr, "minishell: %s: command not found\n", ecmd->argv[0]);
	exit(EXIT_FAILURE);
}

// vim: ts=4 sts=4 sw=4 noet
