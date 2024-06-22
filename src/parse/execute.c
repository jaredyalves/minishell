/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:13:19 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:19 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*cleanup(t_cmd *cmd, t_execute *ecmd, char *error)
{
	free_command(&cmd);
	cmd = (t_cmd *)ecmd;
	free_command(&cmd);
	if (error)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (0);
}

static t_cmd	*invert_redirections(t_cmd *cmd, t_execute *ecmd)
{
	t_redirection	*prev;
	t_redirection	*curr;
	t_redirection	*next;

	prev = 0;
	curr = (t_redirection *)cmd;
	while (curr)
	{
		next = (t_redirection *)curr->cmd;
		curr->cmd = (t_cmd *)prev;
		prev = curr;
		curr = next;
	}
	if (!prev)
		return ((t_cmd *)ecmd);
	curr = prev;
	while (curr->cmd)
		curr = (t_redirection *)curr->cmd;
	curr->cmd = (t_cmd *)ecmd;
	return ((t_cmd *)prev);
}

static int	parse_argument(t_execute *ecmd, char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		token;

	if (ecmd->argc >= ARG_MAX)
		return (3);
	token = get_token(ps, es, &q, &eq);
	if (token == 0)
		return (1);
	if (token != 'a')
		return (2);
	ecmd->argv[ecmd->argc++] = expand_argument(q, eq);
	return (0);
}

t_cmd	*parse_execute(char **ps, char *es)
{
	t_cmd		*cmd;
	t_execute	*ecmd;
	int			status;

	if (peek(ps, es, "(", "("))
		return (parse_block(ps, es));
	ecmd = (t_execute *)execute();
	cmd = parse_redirection(0, ps, es);
	while (!peek(ps, es, TOKENS, TOKENS))
	{
		status = parse_argument(ecmd, ps, es);
		if (status == 1)
			break ;
		if (status == 2)
			return (cleanup(cmd, ecmd, 0));
		if (status == 3)
			return (cleanup(cmd, ecmd, "too many arguments"));
		cmd = parse_redirection(cmd, ps, es);
	}
	if (!cmd && peek(ps, es, "<>", "<>"))
		return (get_token(ps, es, 0, 0), cleanup(cmd, ecmd, 0));
	return (invert_redirections(cmd, ecmd));
}
