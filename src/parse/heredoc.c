/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:38:52 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:38:52 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <readline/readline.h>
#include <stdlib.h>
#include <sys/wait.h>

char		*get_delimiter(const char *q, const char *eq, int *is_quoted);
char		*get_buffer(int fd);

static void	heredoc_eof(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd((char *)delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static void	write_expanded(int fd, char *string)
{
	char	*expanded;
	char	*string_end;

	string_end = string + ms_strlen(string);
	expanded = expand_argument(string, string_end);
	ft_putstr_fd(expanded, fd);
	free(expanded);
}

static void	read_heredoc(int fd, const char *delimiter, int is_quoted)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			heredoc_eof(delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, ms_strlen(delimiter) + 1) == 0)
			break ;
		if (is_quoted)
			ft_putstr_fd(line, fd);
		else
			write_expanded(fd, line);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(line);
}

char	*parse_heredoc(const char *q, const char *eq)
{
	int		fds[2];
	char	*buffer;
	char	*delimiter;
	int		is_quoted;

	pipe1(fds);
	if (fork1() == 0)
	{
		close(fds[0]);
		delimiter = get_delimiter(q, eq, &is_quoted);
		read_heredoc(fds[1], delimiter, is_quoted);
		close(fds[1]);
		return (free(delimiter), NULL);
	}
	close(fds[1]);
	buffer = get_buffer(fds[0]);
	close(fds[0]);
	wait(NULL);
	if (get_sh()->exit_status > 127)
		return (free(buffer), NULL);
	return (buffer);
}
