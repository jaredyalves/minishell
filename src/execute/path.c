#include "ft.h"
#include "minishell.h"

#include <unistd.h>

int	execute_path(const char *name, char **argv, char **envp)
{
	const char	*env_path = ft_getenv("PATH", envp);
	const char	*start = env_path;
	char		path[1024];
	char		*current;

	if (env_path == NULL)
		return (1);
	while (*start)
	{
		current = path;
		while (*start && *start != ':')
			*current++ = *start++;
		*current = '\0';
		if (*start == ':')
			start++;
		ft_strlcat(path, "/", sizeof(path));
		ft_strlcat(path, name, sizeof(path));
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				execve(path, argv, envp);
			return (126);
		}
	}
	return (127);
}
