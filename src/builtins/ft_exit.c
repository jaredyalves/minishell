/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/22 21:41:53 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	char	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	status = (char)get_sh()->exit_status;
	if (args[1])
	{
		if (!is_valid(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			sh_deinit(2);
		}
		status = (char)ft_atoi(args[1]);
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd("too many arguments\n", STDERR_FILENO);
			return (1);
		}
	}
	sh_deinit(status);
}
