/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static pid_t	execute_heredoc_left(int *p, t_redirection *rcmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
	{
		get_sh()->subshell = 1;
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		execute_command(rcmd->cmd);
		wait(0);
	}
	return (pid);
}

static void	execute_heredoc(t_redirection *rcmd)
{
	int		p[2];
	pid_t	pid;
	int		status;

	if (fork1() == 0)
	{
		pipe1(p);
		pid = execute_heredoc_left(p, rcmd);
		ft_putstr_fd(rcmd->buffer, p[1]);
		close(p[0]);
		close(p[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			sh_deinit(WEXITSTATUS(status));
		sh_deinit(EXIT_FAILURE);
	}
	wait(0);
}

static void	execute_redirect(t_redirection *rcmd)
{
	if (fork1() == 0)
	{
		close(rcmd->fd);
		if (open(rcmd->buffer, rcmd->mode, 0664) < 0)
			panic(rcmd->buffer);
		execute_command(rcmd->cmd);
	}
	wait(0);
}

void	execute_redirection(t_redirection *rcmd)
{
	if (rcmd)
	{
		if (rcmd->subtype == REDIRECT)
			execute_redirect(rcmd);
		if (rcmd->subtype == HEREDOC)
			execute_heredoc(rcmd);
	}
}
