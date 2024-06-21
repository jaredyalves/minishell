/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:13:19 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:19 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

char		*double_quotes_ext(char **pq, char *eq);
int			is_valid_env(char *q, int pos);

static char	*single_quotes(char **pq, char *eq)
{
	char	*q;
	char	*str;
	char	*start;
	size_t	len;

	q = *pq;
	start = ++q;
	while (q < eq && *q != '\'')
		q++;
	len = q - start + 1;
	str = (char *)ft_calloc(len, sizeof(char));
	if (!str)
		panic("ft_calloc");
	ft_strlcpy(str, start, len);
	if (q < eq)
		q++;
	*pq = q;
	return (str);
}

static char	*env_variables(char **pq, char *eq)
{
	char	*q;
	char	*env_name;
	char	*env_value;
	char	*start;
	size_t	len;

	q = *pq;
	start = ++q;
	if (!is_valid_env(q, q - start))
		return (*pq = q, ft_strdup("$"));
	while (q < eq && is_valid_env(q, q - start))
		q++;
	len = q - start + 1;
	env_name = (char *)ft_calloc(len, sizeof(char));
	if (!env_name)
		panic("ft_calloc");
	ft_strlcpy(env_name, start, len);
	env_value = ft_getenv(env_name);
	free(env_name);
	*pq = q;
	if (!env_value)
		return (ft_strdup(""));
	return (env_value);
}

static char	*double_quotes(char **pq, char *eq)
{
	char	*q;
	char	*tmp;
	char	*str;

	q = *pq;
	str = 0;
	q++;
	while (q < eq && *q != '"')
	{
		if (*q == '$')
			tmp = env_variables(&q, eq);
		else
			tmp = double_quotes_ext(&q, eq);
		str = concat_strings(str, tmp);
	}
	if (q < eq)
		q++;
	*pq = q;
	return (str);
}

static char	*expand_simple(char **pq, char *eq)
{
	char	*q;
	char	*str;
	char	*start;
	size_t	len;

	q = *pq;
	start = q;
	while (q < eq && *q != '\'' && *q != '"' && *q != '$')
		q++;
	len = q - start + 1;
	str = (char *)ft_calloc(len, sizeof(char));
	if (!str)
		panic("ft_calloc");
	ft_strlcpy(str, start, len);
	*pq = q;
	return (str);
}

char	*expand_argument(char *q, char *eq)
{
	char	*arg;

	if (!q)
		return (0);
	arg = ft_strdup("");
	while (q < eq)
	{
		if (*q == '\'')
			arg = concat_strings(arg, single_quotes(&q, eq));
		else if (*q == '"')
			arg = concat_strings(arg, double_quotes(&q, eq));
		else if (*q == '$')
			arg = concat_strings(arg, env_variables(&q, eq));
		else
			arg = concat_strings(arg, expand_simple(&q, eq));
	}
	return (arg);
}
