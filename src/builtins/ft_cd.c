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

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	check_args(char **args)
{
	if (args[2])
	{
		printf("cd Error : Wrong number of arguments\n");
		return (-1);
	}
	return (0);
}

static void	set_pwd(int flag)
{
	char	directory[4097];
	char	*pwd[3];

	getcwd(directory, sizeof(directory));
	pwd[0] = ft_strdup("export");
	if (flag == 2)
		pwd[1] = ft_strjoin(ft_strdup("OLDPWD="), directory);
	else if (flag == 1)
		pwd[1] = ft_strjoin(ft_strdup("PWD="), directory);
	pwd[2] = NULL;
	ft_export(pwd);
	free(pwd[0]);
	free(pwd[1]);
}

static int	change_to_home(void)
{
	char	*homedir;

	homedir = ft_getenv("HOME");
	if (!homedir)
	{
		printf("cd ERROR: HOME not set\n");
		return (free(homedir), 1);
	}
	chdir(homedir);
	set_pwd(1);
	return (free(homedir), 0);
}

static int	go_back(char *old_pwd)
{
	if (!old_pwd)
	{
		printf("minishell: cd ERROR: OLDPWD not set\n");
		return (free(old_pwd), 1);
	}
	chdir(old_pwd);
	return (0);
}

int	ft_cd(char **args)
{
	char	*old_pwd;
	int		exit;

	old_pwd = ft_getenv("OLDPWD");
	if (check_args(args) == -1)
		return (free(old_pwd), -1);
	set_pwd(2);
	if (!args[1] || args[1] == NULL || (args[1][0] == '~' && !args[1][1]))
		return (free(old_pwd), change_to_home());
	if ((args[1][0] == '-' && !args[1][1]))
	{
		exit = go_back(old_pwd);
		set_pwd(1);
		return (free(old_pwd), exit);
	}
	if (args[1])
	{
		if (chdir(args[1]))
			perror("cd");
	}
	set_pwd(1);
	return (free(old_pwd), 0);
}
