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

#include <unistd.h>
#include <stdio.h>


int	ft_env(char **args)
{
	char	**envp;

	if (args[1])
		{
			ft_putstr_fd("env Error: too many arguments\n", 2);
			return (1);
		}
	envp = get_sh()->env;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
