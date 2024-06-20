#include "minishell.h"

#include <unistd.h>

int	ft_unset(char **old)
{
	(void)old;
	ft_putstr_fd("unset: not implemented\n", STDERR_FILENO);
	return (0);
}
