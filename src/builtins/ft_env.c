/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 16:48:18 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

static void	print(char *name)
{
	char	*value;

	value = ft_getenv(name);
	if (value)
	{
		ft_putstr_fd(name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free(value);
}

int	ft_env(char **args)
{
	char	**envp;
	size_t	i;
	size_t	j;
	char	*name;

	if (args[1])
		return (ft_putstr_fd("minishell: env: arguments aren't supported\n",
				STDERR_FILENO), 1);
	i = 0;
	envp = get_sh()->env;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = (char *) ft_calloc(j + 1, sizeof(char));
		if (!name)
			panic("ft_calloc");
		ft_strlcpy(name, envp[i], j + 1);
		print(name);
		free(name);
		i++;
	}
	return (0);
}
