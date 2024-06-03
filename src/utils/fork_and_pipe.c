#include "minishell.h"

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		exit(1);
	}
	return (pid);
}

int	pipe1(int *pipes)
{
	int	status;

	status = pipe(pipes);
	if (status == -1)
	{
		perror("minishell: pipe");
		exit(1);
	}
	return (status);
}
