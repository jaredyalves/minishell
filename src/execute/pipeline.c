/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static pid_t	execute_pipe_left(int *p, t_pipeline *pcmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
	{
		get_sh()->subshell = 1;
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		execute_command(pcmd->left);
		wait(0);
	}
	return (pid);
}

static pid_t	execute_pipe_right(int *p, t_pipeline *pcmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	if (pid == 0)
	{
		get_sh()->subshell = 1;
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		execute_command(pcmd->right);
		wait(0);
	}
	return (pid);
}

static int	execute_pipe(t_pipeline *pcmd)
{
	int		p[2];
	pid_t	pid[2];
	int		status;

	status = 0;
	pipe1(p);
	pid[0] = execute_pipe_left(p, pcmd);
	pid[1] = execute_pipe_right(p, pcmd);
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], 0, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

void	execute_pipeline(t_pipeline *pcmd)
{
	if (pcmd)
	{
		if (pcmd->subtype == PIPE)
		{
			if (fork1() == 0)
				sh_deinit(execute_pipe(pcmd));
			wait(0);
		}
	}
}
