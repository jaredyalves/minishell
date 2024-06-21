/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 16:10:35 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

static bool	new_line(char **args, int *i)
{
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		*i = 2;
		return (false);

	}
	return (true);
}

int	ft_echo(char **args)
{
	bool	newline;
	int		i;

	i = 1;
	newline = new_line(args, &i);
	while (args[i])
	{
		if (i > 2 || (i > 1 && newline))
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
