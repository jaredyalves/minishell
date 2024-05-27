#include "minishell.h"

t_cmd	*parse_command(char *line)
{
	char	*es;
	t_cmd	*cmd;

	es = line + ft_strlen(line);
	cmd = parse_line(&line, es);
	peek(&line, es, "");
	if (line != es)
		ft_dprintf(STDERR_FILENO, "minishell: leftovers: %s\n", line);
	terminate_line(cmd);
	return (cmd);
}
