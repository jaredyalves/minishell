/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:38:52 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:38:52 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"

#include <stdlib.h>

static char	*unquote(const char *string)
{
	int		i;
	size_t	j;
	size_t	length;
	char	*unquoted;

	if (string == NULL)
		return (NULL);
	length = ms_strlen(string);
	unquoted = (char *)ft_calloc(sizeof(char), length + 1);
	if (unquoted == NULL)
		panic("ft_calloc");
	i = 0;
	j = 0;
	while (j < length)
	{
		if (string[j] != '\'' && string[j] != '"')
			unquoted[i++] = string[j];
		j++;
	}
	return (unquoted);
}

char	*get_delimiter(const char *q, const char *eq, int *is_quoted)
{
	char	*delimiter;
	char	*unquoted;

	*is_quoted = 0;
	delimiter = (char *)ft_calloc(sizeof(char), eq - q + 1);
	ft_strlcpy(delimiter, q, eq - q + 1);
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
	{
		*is_quoted = 1;
		unquoted = unquote(delimiter);
		free(delimiter);
		return (unquoted);
	}
	return (delimiter);
}

char	*get_buffer(int fd)
{
	char	*line;
	char	*buffer;

	buffer = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		buffer = concat_strings(buffer, line);
	}
	return (buffer);
}
