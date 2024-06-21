/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:13:19 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:19 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

char	*concat_strings(char *arg, char *str)
{
	size_t	len;
	char	*dst;

	if (!arg)
		return (str);
	len = ft_strlen(arg) + ft_strlen(str) + 1;
	dst = (char *)ft_calloc(len, sizeof(char));
	if (!dst)
		panic("ft_calloc");
	ft_strlcpy(dst, arg, len);
	if (str)
	{
		ft_strlcat(dst, str, len);
		free(str);
	}
	free(arg);
	return (dst);
}

char	*double_quotes_ext(char **pq, char *eq)
{
	char	*q;
	char	*str;
	char	*start;
	size_t	len;

	q = *pq;
	start = q;
	while (q < eq && *q != '"' && *q != '$')
		q++;
	len = q - start + 1;
	str = (char *)ft_calloc(len, sizeof(char));
	if (!str)
		panic("ft_calloc");
	ft_strlcpy(str, start, len);
	*pq = q;
	return (str);
}

int	is_valid_env(char *q, int pos)
{
	if (pos == 0)
		return (ft_isalnum(*q) || *q == '_' || *q == '?');
	if (pos == 1 && (ft_isdigit(*(q - pos)) || *(q - pos) == '?'))
		return (0);
	return (ft_isalnum(*q) || *q == '_');
}
