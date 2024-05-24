#include "lexer.h"
#include "minishell.h"
#include "run.h"
#include <sys/wait.h>

int runor(t_orcmd *ocmd, char **envp)
{
	int status;

	if (fork1() == 0)
		return (runcmd(ocmd->left, envp));
	waitpid(0, &status, 0);
	if (WIFEXITED(status))
		return (runcmd(ocmd->right, envp));
	return (-1);
}

// vim: ts=4 sts=4 sw=4 noet
