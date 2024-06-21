/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:01:44 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/17 13:01:44 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_block(char **ps, char *es)
{
	t_cmd	*cmd;

	if (peek_next(ps, es, "|)&;", "|)&;"))
		return (0);
	get_token(ps, es, 0, 0);
	cmd = parse_list1(ps, es);
	if (!cmd)
		return (0);
	if (!peek(ps, es, ")", ")"))
		return (free_command(&cmd));
	get_token(ps, es, 0, 0);
	cmd = parse_redirection(cmd, ps, es);
	return (cmd);
}
