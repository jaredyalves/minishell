/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 15:40:27 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

int	ft_unset(char **args)
{
	size_t	i;
	size_t	j;
	char	**envp;

	envp = get_sh()->env;
	while (*++args)
	{
		i = 0;
		while (envp[i] && ft_strncmp(envp[i], *args, ft_strlen(*args)) != 0)
			i++;
		if (envp[i])
		{
			free(envp[i]);
			j = i + 1;
			while (envp[j])
				envp[i++] = envp[j++];
			envp[i] = 0;
		}
	}
	return (0);
}
