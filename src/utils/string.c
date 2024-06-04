#include "minishell.h"

char	*get_str(char *str)
{
	free_str(&str);
	str = readline("minishell ❯ ");
	if (str && *str)
		add_history(str);
	return (str);
}

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
