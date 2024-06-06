#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

char	*get_str(char *str)
{
	free_str(&str);
	str = readline("minishell ❯ ");
	if (str && *str)
		add_history(str);
	return (str);
}
