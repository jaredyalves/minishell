#include "minishell.h"

int	execute_external(t_execcmd *e_command)
{
	char	*name;
	int		status;

	name = e_command->argv[0];
	if (name == NULL)
		return (0);
	status = 127;
	if (ft_strchr(name, '/'))
	{
		if (access(name, F_OK) == 0)
		{
			if (access(name, X_OK) == 0)
				execve(name, e_command->argv, get_shell()->environ);
			status = 126;
		}
	}
	else
		status = execute_from_path(name, e_command->argv, get_shell()->environ);
	if (status == 127)
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", name);
	else if (status == 126)
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", name, strerror(errno));
	return (status);
}
