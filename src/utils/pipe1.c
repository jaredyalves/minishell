#include <unistd.h>

#include "minishell.h"

int	pipe1(int *pipes)
{
	int	status;

	status = pipe(pipes);
	if (status == -1)
		panic("pipe");
	return (status);
}
