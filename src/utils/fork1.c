#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
