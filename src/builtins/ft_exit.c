/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 16:21:01 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>

static int	ft_exit_continue(char**args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (args[1][i] == '-')
			i++;
		if ((args[1][i]) < '0' || (args[1][i]) > '9')
		{
			printf("exit Error: numeric argument required\n");
			printf("Goodbye...See you soon!\n");
			sh_deinit(2);
			return (2);
		}
		i++;
	}
	return (0);
}

int	ft_exit(char **args)
{
	if (args[1])
	{
		if(ft_exit_continue(args) == 2)
			return (2);
	}
	if (args[2])
	{
		printf("exit Error: too many arguments\n");
		return(2);
	}
	printf("Goodbye...See you soon!\n");
	if (args[1])
	{
		sh_deinit(ft_atoi(args[1]));
		return (0);
	}
	sh_deinit(0);
	return (0);
}
