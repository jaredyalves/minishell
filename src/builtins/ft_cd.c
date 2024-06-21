/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 17:43:16 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>

int	ft_cd(char **args)
{
	char	*homedir;

	if (args[2])
	{
		printf("cd Error : Wrong number of arguments\n");
		return (-1);
	}
	if (!args[1] || (args[1][0] == '~' && !args[1][1]))
	{
		homedir = ft_getenv("HOME");
		if(!homedir)
		{
			printf("cd ERROR: HOME not set\n");
			return(free(homedir), 1);
		}
		chdir(homedir);
		return(free(homedir), 0);
	}
	if (args[1])
	{
		chdir(args[1]);
		if(chdir(args[1]))
			perror("cd");
	}
	return (0);
}
