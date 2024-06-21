/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:13:19 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:19 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*search_in_path(char *name, char *path_env)
{
	char	*path;
	char	*start;
	size_t	len;

	path = (char *)ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!path)
		panic("ft_calloc");
	while (*path_env)
	{
		start = path_env;
		while (*path_env && *path_env != ':')
			path_env++;
		len = path_env - start;
		if (len + 2 + ft_strlen(name) >= PATH_MAX)
			break ;
		ft_strlcpy(path, start, len + 1);
		path[len] = '/';
		ft_strlcpy(path + len + 1, name, PATH_MAX);
		if (access(path, F_OK) == 0)
			return (path);
		if (*path_env)
			path_env++;
	}
	return (free(path), (char *)0);
}

static void	path(char *name, char *argv[], char *envp[])
{
	char	*path;
	char	*path_env;

	path_env = ft_getenv("PATH");
	if (path_env)
	{
		path = search_in_path(name, path_env);
		free(path_env);
		if (path)
		{
			if (access(path, X_OK) == 0)
				execve(path, argv, envp);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(path);
			free(path);
			sh_deinit(126);
		}
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": command not found...\n", STDERR_FILENO);
	sh_deinit(127);
}

static void	exec(char *name, char *argv[])
{
	t_sh	*sh;

	sh = get_sh();
	if (ft_strchr(name, '/'))
	{
		if (access(name, F_OK) == 0)
		{
			if (access(name, X_OK) == 0)
				execve(name, argv, sh->env);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(name);
			sh_deinit(126);
		}
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(name);
		sh_deinit(127);
	}
	path(name, argv, sh->env);
}

void	execute_external(t_execute *ecmd)
{
	char	*name;

	name = ecmd->argv[0];
	if (name && *name)
		exec(name, ecmd->argv);
	sh_deinit(EXIT_SUCCESS);
}
