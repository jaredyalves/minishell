#include "minishell.h"

void	search_in_path(char *program, char **argv, char **envp)
{
	int		i;
	char	**paths;
	char	path[PATH_MAX];

	paths = ft_split(getenv("PATH"), ':');
	if (paths == NULL)
		return ;
	i = -1;
	while (paths[++i] != NULL)
	{
		ft_strcpy(path, paths[i]);
		ft_strcat(path, "/");
		ft_strcat(path, program);
		if (access(path, X_OK) == 0)
		{
			execve(path, argv, envp);
			break ;
		}
	}
	i = -1;
	while (paths[++i] != NULL)
		free(paths[i]);
	free(paths);
}

int	runexec(t_execcmd *ecmd, char **envp)
{
	char	*program;

	program = ecmd->argv[0];
	if (program == NULL)
		return (0);
	if (ft_strchr(program, '/'))
		execve(program, ecmd->argv, envp);
	else
		search_in_path(program, ecmd->argv, envp);
	ft_dprintf(STDERR_FILENO, "minishell: %s: Command not found\n", program);
	return (1);
}
