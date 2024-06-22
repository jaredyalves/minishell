/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:57:44 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 16:04:40 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>

static void	heredoc_eof(char *word)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file ", STDERR_FILENO);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static char	*parse_heredoc(char *word)
{
	char	*buffer;
	char	*line;
	char	*line_expanded;

	buffer = ft_strdup("");
	while (1)
	{
		line = get_line("> ");
		line_expanded = expand_argument(line, line + ft_strlen(line));
		free(line);
		if (!line_expanded)
		{
			heredoc_eof(word);
			break ;
		}
		if (ft_strncmp(word, line_expanded, ft_strlen(word) + 1) == 0)
			break ;
		buffer = concat_strings(buffer, line_expanded);
		buffer = ft_strjoin(buffer, "\n");
	}
	free(line_expanded);
	return (buffer);
}

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
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		execute_command(rcmd->cmd);
		wait(0);
	}
	return (pid);
}

void	execute_heredoc(t_redirection *rcmd)
{
	int		p[2];
	pid_t	pid;
	int		status;
	char	*buffer;

	if (fork1() == 0)
	{
		status = 0;
		pipe1(p);
		pid = execute_heredoc_left(p, rcmd);
		buffer = parse_heredoc(rcmd->buffer);
		ft_putstr_fd(buffer, p[1]);
		free(buffer);
		close(p[0]);
		close(p[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			sh_deinit(WEXITSTATUS(status));
		sh_deinit(EXIT_FAILURE);
	}
	wait(0);
}
