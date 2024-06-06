#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
