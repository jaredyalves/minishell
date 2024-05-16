#include "../lexer/lexer.h"
#include "../nulterminate/nulterminate.h"
#include "parser.h"
#include "run/run.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIXME: Can't use strlen(), replace with a ft function
// FIXME: Can't use fprintf(), replace with a ft function
t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if (s != es)
	{
		fprintf(stderr, "minishell: leftovers: %s\n", s);
		freecmd(cmd);
		exit(EXIT_FAILURE);
	}
	nulterminate(cmd);
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
