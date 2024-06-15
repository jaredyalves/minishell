#include "libft.h"
#include "minishell.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

static void	sigint_handler(int sig)
{
	t_sh	*sh;

	(void)sig;
	sh = get_sh();
	sh->exit_status = 130;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		panic("signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		panic("signal");
}
