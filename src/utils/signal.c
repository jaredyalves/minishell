#include "minishell.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

static void	sigint_handler(int sig, siginfo_t *info, void *ucontext)
{
	t_sh	*sh;

	(void)sig;
	(void)ucontext;
	if (info->si_pid != 0)
	{
		sh = get_sh();
		sh->exit_status = 130;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGINT, &sa, 0) == -1)
		panic("sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		panic("signal");
}
