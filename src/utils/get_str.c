#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

#include "minishell.h"

char	*get_str(const t_ms *ms, char *str)
{
	const char	*prompt = "\033[1;31m[minishell]\033[0m \033[1;32m❯\033[0m ";

	free_str(&str);
	if (ms->exit_status != 0)
		prompt = "\033[1;31m[minishell]\033[0m \033[1;31m❯\033[0m ";
	str = readline(prompt);
	if (str && *str)
		add_history(str);
	return (str);
}
