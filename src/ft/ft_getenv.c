#include "minishell.h"

char	*ft_getenv(const char *name)
{
	char		**env;
	size_t		name_len;
	const char	*env_name;
	const char	*p;

	if (name == NULL || *name == '\0')
		return (NULL);
	env = get_shell()->environ;
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
			return ((char *)(env_name + 1));
		env++;
	}
	return (NULL);
}
