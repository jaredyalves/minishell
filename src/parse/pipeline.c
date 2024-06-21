/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:01:44 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/17 13:01:44 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_pipeline(char **ps, char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parse_execute(ps, es);
	if (!cmd)
		return (0);
	if (peek(ps, es, "|", ""))
	{
		if (peek_next(ps, es, "|)&;", "|)&;"))
			return (free_command(&cmd));
		token = get_token(ps, es, 0, 0);
		if (token == '|')
			cmd = pipeline(PIPE, cmd, parse_pipeline(ps, es));
		if (!((t_pipeline *)cmd)->right)
			return (free_command(&cmd));
	}
	return (cmd);
}
