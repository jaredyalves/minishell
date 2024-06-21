/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

static void	check_syntax(char **ps, char *es)
{
	char	*s;
	int		token;

	s = *ps;
	token = get_token(&s, es, 0, 0);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token == 0)
		ft_putstr_fd("newline", STDERR_FILENO);
	else if (token < 0)
	{
		token = -token;
		ft_putchar_fd(token, STDERR_FILENO);
	}
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	get_sh()->exit_status = 2;
}

static int	check_leftovers(char **ps, char *es)
{
	char	*s;

	s = *ps;
	peek(&s, es, "", "");
	if (s != es)
	{
		check_syntax(ps, es);
		return (1);
	}
	*ps = s;
	return (0);
}

t_cmd	*parse_command(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	if (peek(&s, es, "|&;", "|&;"))
		cmd = 0;
	else
		cmd = parse_list1(&s, es);
	if (!cmd)
	{
		check_syntax(&s, es);
		return (0);
	}
	if (check_leftovers(&s, es))
		return (free_command(&cmd));
	return (cmd);
}
