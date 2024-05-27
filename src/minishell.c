#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;

	(void)argc;
	(void)argv;
	i = -1;
	while (envp[++i] != NULL)
		get_shell()->environ[i] = envp[i];
	get_shell()->environ[i] = NULL;
	while (1)
	{
		get_shell()->cmdline = get_line(get_shell()->cmdline);
		if (fork1() == 0)
		{
			get_shell()->command = parse_command(get_shell()->cmdline);
			get_shell()->status = runcmd(get_shell()->command);
			free_command(get_shell()->command);
			if (get_shell()->status == 0)
				exit(EXIT_SUCCESS);
			exit(EXIT_FAILURE);
		}
		wait(0);
	}
}
