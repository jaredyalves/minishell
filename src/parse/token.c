/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:13:19 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:19 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_quote(char **ps, char *es)
{
	char	*s;
	int		quote;

	s = *ps;
	quote = *s++;
	while (s < es && *s != quote)
		s++;
	if (s < es)
		s++;
	*ps = s;
}

int	parse_token(char **ps, char *es)
{
	char	*s;
	int		token;

	s = *ps;
	token = 0;
	if (s < es && ft_strchr(TOKENS, *s))
	{
		token = *s++;
		if (*s != '(' && *s != ')' && s < es && *s == *(s - 1))
			token = -*s++;
	}
	else if (s < es)
	{
		token = 'a';
		while (s < es && !ft_strchr(BLANKS, *s) && !ft_strchr(TOKENS, *s))
		{
			if (*s == '\'' || *s == '"')
				parse_quote(&s, es);
			else
				s++;
		}
	}
	*ps = s;
	return (token);
}

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		token;

	s = *ps;
	while (s < es && ft_strchr(BLANKS, *s))
		s++;
	if (q)
		*q = s;
	token = parse_token(&s, es);
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(BLANKS, *s))
		s++;
	*ps = s;
	return (token);
}

int	peek(char **ps, char *es, char *s_tokens, char *d_tokens)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(BLANKS, *s))
		s++;
	*ps = s;
	if (*s && *s != *(s + 1))
		return (ft_strchr(s_tokens, *s) != 0);
	if (*s && *s == *(s + 1))
		return (ft_strchr(d_tokens, *s) != 0);
	return (0);
}

int	peek_next(char **ps, char *es, char *s_tokens, char *d_tokens)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(BLANKS, *s))
		s++;
	*ps = s;
	get_token(&s, es, 0, 0);
	if (*s && *s != *(s + 1))
		return (ft_strchr(s_tokens, *s) != 0);
	if (*s && *s == *(s + 1))
		return (ft_strchr(d_tokens, *s) != 0);
	if (!*s)
		return (1);
	return (0);
}
