#include "libft.h"
#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>

int	is_builtin(t_execute *ecmd)
{
	char	*name;

	name = ecmd->argv[0];
	if (name && *name)
	{
		if (ft_strncmp(name, "echo", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "pwd", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "export", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "unset", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "env", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "exit", ft_strlen(name) + 1) == 0)
			return (1);
	}
	return (0);
}

void	execute_builtin(t_execute *ecmd)
{
	char	*name;

	name = ecmd->argv[0];
	if (name && *name)
	{
		if (ft_strncmp(name, "echo", ft_strlen(name) + 1) == 0)
			ft_putstr_fd("echo: not implemented\n", STDERR_FILENO);
		if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0)
			ft_putstr_fd("cd: not implemented\n", STDERR_FILENO);
		if (ft_strncmp(name, "pwd", ft_strlen(name) + 1) == 0)
			ft_putstr_fd("pwd: not implemented\n", STDERR_FILENO);
		if (ft_strncmp(name, "export", ft_strlen(name) + 1) == 0)
			ft_putstr_fd("export: not implemented\n", STDERR_FILENO);
		if (ft_strncmp(name, "unset", ft_strlen(name) + 1) == 0)
			ft_putstr_fd("unset: not implemented\n", STDERR_FILENO);
		if (ft_strncmp(name, "env", ft_strlen(name) + 1) == 0)
			ft_putstr_fd("env: not implemented\n", STDERR_FILENO);
		if (ft_strncmp(name, "exit", ft_strlen(name) + 1) == 0)
			ft_putstr_fd("exit: not implemented\n", STDERR_FILENO);
	}
	sh_deinit(EXIT_SUCCESS);
}
