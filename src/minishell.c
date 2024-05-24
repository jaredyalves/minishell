#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	static char *line = NULL;
	t_cmd		*cmd;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = get_line(line);
		if (fork1() == 0)
		{
			cmd = parsecmd(line);
			if (runcmd(cmd, envp) == -1)
			{
				freecmd(cmd);
				exit(EXIT_FAILURE);
			}
			free(line);
			exit(EXIT_SUCCESS);
		}
		wait(0);
	}
}
