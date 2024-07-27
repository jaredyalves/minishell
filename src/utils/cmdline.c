#include "minishell.h"

#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

char	*get_cmdline(t_ms *ms)
{
	if (ms->cmdline)
		free(ms->cmdline);
	ms->cmdline = readline("$ ");
	if (ms->cmdline == NULL)
		return (NULL);
	if (*ms->cmdline)
		add_history(ms->cmdline);
	return (ms->cmdline);
}
