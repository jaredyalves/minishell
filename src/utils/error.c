#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ft.h"

void	panic(const char *err)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, err, ft_strlen(err));
	if (strerror(errno))
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	}
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
