#include "minishell.h"
#include "parser.h"
#include "run.h"
#include <string.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	static char *line = NULL;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = get_line(line);
		if (fork1() == 0)
			runcmd(parsecmd(line), envp);
		wait(0);
	}
}

// vim: ts=4 sts=4 sw=4 noet
