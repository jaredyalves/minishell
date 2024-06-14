#include "ft.h"
#include "minishell.h"

#include <unistd.h>

t_cmd	*parse_command(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parse_list(&s, es);
	if (cmd == NULL)
		return (NULL);
	peek(&s, es, "", "");
	if (s != es)
	{
		ft_dprintf(STDERR_FILENO, "minishell: leftovers: %s\n", s);
		free_cmd(&cmd);
		return (NULL);
	}
	terminate(cmd);
	return (cmd);
}
