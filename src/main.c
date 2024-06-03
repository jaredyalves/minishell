#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	init_shell(argc, argv, envp);
	setup_signal_handlers();
	shell = get_shell();
	while (shell->stop == 0)
	{
		shell->cmdline = get_line(shell->cmdline);
		if (shell->cmdline == NULL)
			break ;
		shell->command = parse_cmdline(shell->cmdline);
		if (shell->command && fork1() == 0)
		{
			shell->exit_status = execute(shell->command);
			exit(cleanup_shell());
		}
		waitpid(0, &shell->status, 0);
		free_command(&shell->command);
		free_line(&shell->cmdline);
	}
	exit(cleanup_shell());
}
