/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/23 09:11:50 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print(char **args)
{
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
		args++;
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	while (*++args && (*args)[i] == '-')
	{
		while ((*args)[++i])
		{
			if ((*args)[i] == 'n')
				newline = 0;
			else if ((*args)[i] != '\0')
			{
				ft_putstr_fd("minishell: echo: -", STDERR_FILENO);
				ft_putchar_fd((*args)[i], STDERR_FILENO);
				ft_putstr_fd(": invalid option\n", STDERR_FILENO);
				return (2);
			}
		}
		i = 0;
	}
	print(args);
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
