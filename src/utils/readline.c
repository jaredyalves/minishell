#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

void	get_str(void)
{
	t_sh	*sh;

	sh = get_sh();
	if (sh->str)
	{
		free(sh->str);
		sh->str = 0;
	}
	if (sh->exit_status != 0)
		sh->str = readline(RED_BOLD "[minishell] " RESET RED_BOLD "❯ " RESET);
	else
		sh->str = readline(RED_BOLD "[minishell] " RESET GREEN_BOLD "❯ " RESET);
	if (sh->str && *sh->str)
		add_history(sh->str);
}
