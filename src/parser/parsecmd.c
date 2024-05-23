#include "ft.h"
#include "lexer.h"
#include "parser.h"
#include "run.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FIXME: Can't use strlen(), replace with a ft function
t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + strlen(s);
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

// vim: ts=4 sts=4 sw=4 noet
