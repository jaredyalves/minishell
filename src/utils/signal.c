/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/wait.h>

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

static void	sigchld_handler(int sig, siginfo_t *info, void *ucontext)
{
	t_sh	*sh;

	(void)sig;
	(void)ucontext;
	sh = get_sh();
	sh->exit_status = info->si_status;
	if (info->si_code != CLD_EXITED)
	{
		sh->exit_status += 128;
		if (info->si_status == SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (info->si_status == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

void	handle_signals(void)
{
	struct sigaction	sa;

	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		panic("signal");
	sa.sa_sigaction = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGINT, &sa, 0) == -1)
		panic("sigaction");
	sa.sa_sigaction = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO | SA_NOCLDSTOP;
	if (sigaction(SIGCHLD, &sa, 0) == -1)
		panic("sigaction");
}
