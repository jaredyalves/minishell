#include "minishell.h"

static void	error_message(char *name, const int status)
{
	if (status == 127)
		ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", name);
	else if (status == 126)
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", name, strerror(errno));
}

static void	free_argv(char **argv)
{
	int	i;

	if (argv == NULL)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	execute_external(t_ms *ms, t_execcmd *cmd)
{
	char	*name;
	int		status;
	char	**argv;

	argv = expand_arguments(cmd->argv, ms->env);
	name = argv[0];
	if (name == NULL || *name == '\0')
		return (free_argv(argv), ms->exit_status);
	if (ft_strchr(name, '/'))
	{
		status = 127;
		if (access(name, F_OK) == 0)
		{
			if (access(name, X_OK) == 0)
				execve(name, argv, ms->env);
			status = 126;
		}
	}
	else
		status = execute_path(name, argv, ms->env);
	error_message(name, status);
	return (free_argv(argv), status);
}
