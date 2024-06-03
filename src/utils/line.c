#include "minishell.h"

char	*get_line(char *line)
{
	free_line(&line);
	line = readline("minishell ❯ ");
	if (line && *line)
		add_history(line);
	return (line);
}

void	free_line(char **p_line)
{
	if (p_line && *p_line)
	{
		free(*p_line);
		*p_line = NULL;
	}
}
