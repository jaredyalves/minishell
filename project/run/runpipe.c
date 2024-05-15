#include "../lexer/lexer.h"
#include "../minishell.h"
#include "run.h"
#include <sys/wait.h>
#include <unistd.h>

void	runpipe(t_pipecmd *pcmd)
{
	int	p[2];

	if (pipe(p) < 0)
		panic("minishell: pipe error");
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left);
	}
	if (fork() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
}

// vim: ts=4 sts=4 sw=4 noet
