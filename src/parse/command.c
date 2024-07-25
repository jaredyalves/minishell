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

#include "libft.h"
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

static int	check_quotes(const char *string)
{
	int	single_quotes;
	int	double_quotes;
	int	inside_single_quotes;
	int	inside_double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	inside_single_quotes = 0;
	inside_double_quotes = 0;
	while (*string)
	{
		if (*string == '\'' && !inside_double_quotes)
		{
			inside_single_quotes = !inside_single_quotes;
			single_quotes++;
		}
		else if (*string == '\"' && !inside_single_quotes)
		{
			inside_double_quotes = !inside_double_quotes;
			double_quotes++;
		}
		string++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
}

t_cmd	*parse_command(char *s)
{
	char	*es;
	t_cmd	*cmd;

	if (!check_quotes(s))
		return (ft_putstr_fd("minishell: unclosed quotes\n", 2), NULL);
	es = s + ms_strlen(s);
	if (peek(&s, es, "|&;", "|&;"))
		cmd = 0;
	else
		cmd = parse_list1(&s, es);
	if (cmd == NULL && get_sh()->heredoc == 1)
	{
		if (get_sh()->subshell == 1)
			sh_deinit(get_sh()->exit_status);
		get_sh()->heredoc = 0;
		return (NULL);
	}
	if (cmd == NULL)
		return (check_syntax(&s, es), NULL);
	if (check_leftovers(&s, es))
		return (free_command(&cmd));
	return (cmd);
}
