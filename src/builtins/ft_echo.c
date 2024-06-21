/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 19:39:36 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

static int	ft_op_strchr(char *s, int c)
{
	while ((char)c == *s)
	{
		s++;
		if(!*s)
			return (0);
	}
	return (1);
}

static int	ft_check_options(char **args, int *i)
{
	int	j;
	int	t;

	t = *i;
	j = 1;
	while(args[j] && !ft_strncmp(args[j], "-", 1))
	{
		if(ft_op_strchr(&args[j][1], 'n'))
		{
			ft_putstr_fd("minishell: echo Error: not compatible options\n", 2);
			return (1);
		}
		j++;
		t++;
	}
	*i = t;
	return (0);
}

static bool	ft_new_line(char **args)
{
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
		return (false);
	return (true);
}

int	ft_echo(char **args)
{
	bool	newline;
	int		i;

	i = 1;
	newline = ft_new_line(args);
	if(ft_check_options(args, &i))
		return(1);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
