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
			runcmd(parse_cmdline(get_shell()->cmdline));
		wait(0);
	}
}
