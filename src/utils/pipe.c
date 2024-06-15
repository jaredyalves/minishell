#include "minishell.h"

#include <unistd.h>

int	pipe1(int *pipes)
{
	int	status;

	status = pipe(pipes);
	if (status == -1)
		panic("pipe");
	return (status);
}
