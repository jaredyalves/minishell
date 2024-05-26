#include "minishell.h"

t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
		ft_dprintf(STDERR_FILENO, "minishell: leftovers: %s\n", s);
	terminate_line(cmd);
	return (cmd);
}
