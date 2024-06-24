/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 20:21:33 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_execute *ecmd)
{
	char	*name;

	name = ecmd->argv[0];
	if (name && *name)
	{
		if (ft_strncmp(name, "echo", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "pwd", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "export", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "unset", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "env", ft_strlen(name) + 1) == 0)
			return (1);
		if (ft_strncmp(name, "exit", ft_strlen(name) + 1) == 0)
			return (1);
	}
	return (0);
}

static int	has_options(char **args)
{
	if (args[1])
		if (args[0] && args[1][0] == '-' && !args[1][1])
			return (0);
	if (args[1] && args[1][0] == '-')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(" error: options are not supported\n", 2);
		return (1);
	}
	return (0);
}

void	execute_builtin(t_execute *ecmd)
{
	int		exit_status;
	char	*name;

	exit_status = 0;
	name = ecmd->argv[0];
	if (ft_strncmp(name, "echo", ft_strlen(name) + 1) == 0)
		exit_status = ft_echo(ecmd->argv);
	else if (ft_strncmp(name, "exit", ft_strlen(name) + 1) == 0)
		exit_status = ft_exit(ecmd->argv);
	else if (!has_options(ecmd->argv))
	{
		if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0)
			exit_status = ft_cd(ecmd->argv);
		else if (ft_strncmp(name, "pwd", ft_strlen(name) + 1) == 0)
			exit_status = ft_pwd(ecmd->argv);
		else if (ft_strncmp(name, "export", ft_strlen(name) + 1) == 0)
			exit_status = ft_export(ecmd->argv);
		else if (ft_strncmp(name, "unset", ft_strlen(name) + 1) == 0)
			exit_status = ft_unset(ecmd->argv);
		else if (ft_strncmp(name, "env", ft_strlen(name) + 1) == 0)
			exit_status = ft_env(ecmd->argv);
	}
	get_sh()->exit_status = exit_status;
	if (get_sh()->subshell == 1)
		sh_deinit(exit_status);
}
