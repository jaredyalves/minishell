#include "minishell.h"

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
	int		exit_status;
	char	*name;

	exit_status = 0;
	name = ecmd->argv[0];
	if (ft_strncmp(name, "echo", ft_strlen(name) + 1) == 0)
		exit_status = ft_echo(ecmd->argv);
	else if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0)
		exit_status = ft_cd(ecmd->argv);
	else if (ft_strncmp(name, "pwd", ft_strlen(name) + 1) == 0)
		exit_status = ft_pwd();
	else if (ft_strncmp(name, "export", ft_strlen(name) + 1) == 0)
		exit_status = ft_export(ecmd->argv);
	else if (ft_strncmp(name, "unset", ft_strlen(name) + 1) == 0)
		exit_status = ft_unset(ecmd->argv);
	else if (ft_strncmp(name, "env", ft_strlen(name) + 1) == 0)
		exit_status = ft_env();
	else if (ft_strncmp(name, "exit", ft_strlen(name) + 1) == 0)
		exit_status = ft_exit(ecmd->argv);
	get_sh()->exit_status = exit_status;
	if (get_sh()->subshell == 1)
		sh_deinit(exit_status);
}
