/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>

size_t	ms_strlen(const char *string)
{
	size_t	length;

	if (string == NULL)
		return (0);
	length = 0;
	while (string[length])
		length++;
	return (length);
}

char	*ms_strjoin(char *string1, const char *string2)
{
	size_t	length;
	char	*destination;

	if (string1 == NULL || string2 == NULL)
		return (NULL);
	length = ms_strlen(string1) + ms_strlen(string2) + 1;
	destination = (char *)ft_calloc(sizeof(char), length);
	if (destination == NULL)
		return (NULL);
	ft_strlcpy(destination, string1, length);
	ft_strlcat(destination, string2, length);
	free(string1);
	return (destination);
}

char	*ms_strreplace(char *string, char *old, char new)
{
	int		i;
	char	*new_string;

	if (string == NULL)
		return (NULL);
	new_string = ft_strdup(string);
	if (new_string == NULL)
		panic("ft_strdup");
	i = 0;
	while (new_string[i])
	{
		if (ft_strchr(old, new_string[i]))
			new_string[i] = new;
		i++;
	}
	return (free(string), new_string);
}

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
