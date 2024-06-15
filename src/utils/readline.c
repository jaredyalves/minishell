#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

static void	free_str(void)
{
	t_sh	*sh;

	sh = get_sh();
	if (sh->str)
	{
		free(sh->str);
		sh->str = 0;
	}
}

int	get_str(void)
{
	static char	prompt_ok[] = RED_BOLD "[minishell] " RESET GREEN_BOLD "❯ " RESET;
	static char	prompt_not_ok[] = RED_BOLD "[minishell] " RESET RED_BOLD "❯ " RESET;
	t_sh		*sh;

	sh = get_sh();
	free_str();
	if (sh->exit_status != 0)
		sh->str = readline(prompt_not_ok);
	else
		sh->str = readline(prompt_ok);
	if (!sh->str)
		return (0);
	if (sh->str && *sh->str)
		add_history(sh->str);
	return (1);
}
