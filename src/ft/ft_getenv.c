#include "minishell.h"

char	*ft_getenv(char *name, char **envp)
{
	char	**env;
	size_t	name_len;
	char	*env_name;
	char	*p;

	if (name == NULL || *name == '\0')
		return (NULL);
	env = envp;
	name_len = 0;
	while (name[name_len])
		name_len++;
	while (*env)
	{
		env_name = *env;
		p = name;
		while (*p && *env_name++ == *p++)
			;
		if (*p == '\0' && *env_name == '=')
			return (env_name + 1);
		env++;
	}
	return (NULL);
}
