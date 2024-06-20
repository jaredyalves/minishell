#include "minishell.h"

#include <unistd.h>

int	ft_export(char **new)
{
	(void)new;
	ft_putstr_fd("export: not implemented\n", STDERR_FILENO);
	return (0);
}
