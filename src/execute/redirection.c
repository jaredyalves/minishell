/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 09:58:36 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>
#include <sys/wait.h>

void	execute_heredoc(t_redirection *rcmd);

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
