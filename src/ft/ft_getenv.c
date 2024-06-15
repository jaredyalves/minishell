#include "libft.h"
#include "minishell.h"

static int	is_special(char *name)
{
	if (ft_strncmp(name, "?", ft_strlen(name) + 1) == 0)
		return (1);
	return (0);
}

static char	*special(char *name)
{
	if (ft_strncmp(name, "?", ft_strlen(name) + 1) == 0)
		return (ft_itoa(get_sh()->exit_status));
	return (0);
}

char	*ft_getenv(char *name)
{
	char	**envp;
	char	*env;
	char	*ptr;

	if (!name || !*name)
		return (0);
	if (is_special(name))
		return (special(name));
	envp = get_sh()->env;
	while (*envp)
	{
		env = *envp;
		ptr = name;
		while (*env == *ptr && *ptr != '\0')
		{
			env++;
			ptr++;
		}
		if (*ptr == '\0' && *env == '=')
			return (ft_strdup(env + 1));
		envp++;
	}
	return (0);
}
