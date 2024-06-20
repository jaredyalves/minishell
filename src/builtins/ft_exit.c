#include "minishell.h"

#include <unistd.h>

int	ft_exit(char **args)
{
	(void)args;
	ft_putstr_fd("exit: not implemented\n", STDERR_FILENO);
	return (0);
}
