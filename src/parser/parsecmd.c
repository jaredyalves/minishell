#include "ft.h"
#include "lexer.h"
#include "parser.h"
#include "run.h"
#include <stdlib.h>
#include <unistd.h>

t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		freecmd(cmd);
		ft_dprintf(STDERR_FILENO, "minishell: leftovers: %s\n", s);
		exit(EXIT_FAILURE);
	}
	terminate_line(cmd);
	return (cmd);
}
