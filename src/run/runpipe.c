#include "lexer.h"
#include "minishell.h"
#include "run.h"
#include <sys/wait.h>
#include <unistd.h>

int runpipe(t_pipecmd *pcmd, char **envp)
{
	int	p[2];

	if (pipe(p) < 0)
		panic("pipe", (t_cmd *)pcmd);
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		return (runcmd(pcmd->left, envp));
	}
	if (fork() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		return (runcmd(pcmd->right, envp));
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	return (0);
}

// vim: ts=4 sts=4 sw=4 noet
