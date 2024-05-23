#include "minishell.h"
#include "parser.h"
#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// FIXME: Can't use fprintf(), replace with a ft function
// FIXME: Can't use memset(), replace with a ft function
int	getcmd(char *buf, int nbuf)
{
	fprintf(stderr, "> ");
	memset(buf, 0, nbuf);
	gets(buf, nbuf);
	if (buf[0] == 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	buf[1000];

	(void)argc;
	(void)argv;
	while (1)
	{
		if (getcmd(buf, sizeof(buf)) < 0)
			break ;
		if (fork1() == 0)
			runcmd(parsecmd(buf), envp);
		wait(0);
	}
	exit(EXIT_SUCCESS);
}

// vim: ts=4 sts=4 sw=4 noet
