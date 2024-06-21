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

#include <unistd.h>
#include <stdio.h>

int	ft_unset(char **old)
{
	char	**envp;
	size_t	old_len;
	char	**next;

	envp = get_sh()->env;
	old_len = ft_strlen(old[1]);
	while (*envp)
	{
		if (ft_strncmp(*envp, old[1], old_len) == 0 && (*envp)[old_len] == '=')
		{
			next = envp;
			free(*envp);
			while (*next)
			{
				*next = *(next + 1);
				next++;
			}
			return (0);
		}
		envp++;
	}
	return (1);
}
