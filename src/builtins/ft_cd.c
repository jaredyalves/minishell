#include "minishell.h"

#include <unistd.h>

int	ft_cd(char **args)
{
	(void)args;
	ft_putstr_fd("cd: not implemented\n", STDERR_FILENO);
	return (0);
}
