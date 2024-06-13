#include "ft.h"
#include "minishell.h"

#include <unistd.h>

t_cmd	*parse(char *str)
{
	char	*es;
	t_cmd	*cmd;

	es = str + ft_strlen(str);
	cmd = parse_list(&str, es);
	if (cmd == NULL)
		return (NULL);
	peek(&str, es, "", "");
	if (str != es)
	{
		ft_dprintf(STDERR_FILENO, "minishell: leftovers: %s\n", str);
		free_cmd(&cmd);
		return (NULL);
	}
	terminate(cmd);
	return (cmd);
}
