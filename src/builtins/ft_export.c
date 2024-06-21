/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 17:04:41 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>

/* int	remove_white_spaces() */

int	ft_export(char **new)
{
	char	**envp;
	char	*equal_sign;

	if ((!new[1]))
		return (ft_env(new));
	envp = get_sh()->env;
	equal_sign = ft_strchr(new[1], '=');
	if (!equal_sign)
		return (1);
	while (*envp)
	{
		if (ft_strncmp(*envp, new[1], equal_sign - new[1]) == 0 && \
				(*envp)[equal_sign - new[1]] == '=')
		{
			free(*envp);
			*envp = ft_strdup(new[1]);
			return (0);
		}
		envp++;
	}
	if ((envp - get_sh()->env) >= ARG_MAX - 1)
		return (1);
	*envp = ft_strdup(new[1]);
	*(envp + 1) = NULL;
	return (0);
}
