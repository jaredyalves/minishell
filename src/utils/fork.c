#include "minishell.h"

#include <signal.h>
#include <unistd.h>

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
			panic("signal");
		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
			panic("signal");
	}
	else if (pid == -1)
		panic("fork");
	return (pid);
}
