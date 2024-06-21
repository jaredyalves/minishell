/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:38:52 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:38:52 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>

t_cmd	*handle_redirection(t_cmd *cmd, int token, char *q, char *eq)
{
	t_redirection	*rcmd;

	if (token == - '<')
		cmd = redirection(HEREDOC, cmd, 0, 0);
	if (token == '<')
		cmd = redirection(REDIRECT, cmd, O_RDONLY, 0);
	if (token == '>')
		cmd = redirection(REDIRECT, cmd, O_WRONLY | O_CREAT | O_TRUNC, 1);
	if (token == - '>')
		cmd = redirection(REDIRECT, cmd, O_WRONLY | O_CREAT | O_APPEND, 1);
	rcmd = (t_redirection *)cmd;
	rcmd->buffer = expand_argument(q, eq);
	return (cmd);
}

t_cmd	*parse_redirection(t_cmd *cmd, char **ps, char *es)
{
	char	*eq;
	char	*q;
	int		token;
	int		next_token;

	while (peek(ps, es, "<>", "<>"))
	{
		if (peek_next(ps, es, TOKENS, TOKENS))
			return (free_command(&cmd));
		token = get_token(ps, es, 0, 0);
		next_token = get_token(ps, es, &q, &eq);
		if (next_token != 'a')
			return (free_command(&cmd));
		cmd = handle_redirection(cmd, token, q, eq);
	}
	return (cmd);
}
