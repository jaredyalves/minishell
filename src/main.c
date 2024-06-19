#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static void	wait_for_child(void)
{
	t_sh	*sh;

	sh = get_sh();
	waitpid(0, &sh->wait_status, 0);
	if (WIFEXITED(sh->wait_status))
		sh->exit_status = WEXITSTATUS(sh->wait_status);
	else if (WIFSIGNALED(sh->wait_status))
	{
		sh->term_signal = WTERMSIG(sh->wait_status);
		if (sh->term_signal == SIGINT)
		{
			sh->exit_status = 130;
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		else if (sh->term_signal == SIGQUIT)
		{
			sh->exit_status = 131;
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		}
	}
}

static int	keep_running(void)
{
	t_sh	*sh;

	sh = get_sh();
	get_str();
	if (!sh->str)
		return (0);
	if (*sh->str)
	{
		if (fork1() == 0)
		{
			sh->cmd = parse_command(sh->str);
			execute_command(sh->cmd);
		}
		wait_for_child();
		free_command(&sh->cmd);
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	sh_init(argc, argv, envp);
	while (keep_running())
		;
	sh_deinit(EXIT_SUCCESS);
}
