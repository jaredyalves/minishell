#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	static char *line = NULL;
	t_cmd		*command;
	int			 status;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = get_line(line);
		if (fork1() == 0)
		{
			command = parsecmd(line);
			status = runcmd(command, envp);
			free_command(command);
			free(line);
			if (status == 0)
				exit(EXIT_SUCCESS);
			exit(EXIT_FAILURE);
		}
		wait(0);
		free(line);
		line = NULL;
	}
}
