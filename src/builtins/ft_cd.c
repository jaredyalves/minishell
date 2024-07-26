/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/07/24 17:52:11 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

static int	check_args(char **args)
{
	int	count;

	if (args == NULL)
	{
		ft_putstr_fd("minishell: cd: something went wrong\n", STDERR_FILENO);
		return (0);
	}
	count = 0;
	while (args[count])
		count++;
	if (count > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static void	update_env_vars(char *old_pwd)
{
	char	pwd[PATH_MAX];
	char	*cmd[3];

	getcwd(pwd, sizeof(pwd));
	cmd[0] = "export";
	cmd[2] = NULL;
	cmd[1] = ft_strjoin("OLDPWD=", old_pwd);
	ft_export(cmd);
	free(cmd[1]);
	cmd[1] = ft_strjoin("PWD=", pwd);
	ft_export(cmd);
	free(cmd[1]);
}

static int	change_directory(char *path, int print_path)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (free(path), 1);
	}
	update_env_vars(pwd);
	if (print_path)
		ft_putendl_fd(path, STDOUT_FILENO);
	return (free(path), 0);
}

int	ft_cd(char **args)
{
	char	*path;

	if (!check_args(args))
		return (1);
	if (args[1] == NULL || (args[1] && ft_strncmp(args[1], "~", 2) == 0))
	{
		path = ft_getenv("HOME");
		if (path == NULL)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		return (change_directory(path, 0));
	}
	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
	{
		path = ft_getenv("OLDPWD");
		if (path == NULL)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		return (change_directory(path, 1));
	}
	if (args[1])
		return (change_directory(ft_strdup(args[1]), 0));
	return (1);
}
