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
