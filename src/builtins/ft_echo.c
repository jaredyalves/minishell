#include "minishell.h"

#include <unistd.h>

int	ft_echo(char **args)
{
	(void)args;
	ft_putstr_fd("echo: not implemented\n", STDERR_FILENO);
	return (0);
}
