#include "minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (shell == NULL)
	{
		shell = (t_shell *)malloc(sizeof(*shell));
		if (shell == NULL)
		{
			ft_dprintf(STDERR_FILENO, "minishell: malloc", strerror(errno));
			ft_dprintf(STDERR_FILENO, ": %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		ft_memset(shell, 0, sizeof(*shell));
	}
	return (shell);
}
