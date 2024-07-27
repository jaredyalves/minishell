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

#include "libft.h"
#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static int	check_path(char *path, int to_free)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		panic("stat");
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		if (to_free)
			free(path);
		sh_deinit(126);
	}
	if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

static char	*search_in_path(char *name, char *path_env)
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
		if (len + 2 + ms_strlen(name) >= PATH_MAX)
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
			if (check_path(path, 1))
				execve(path, argv, envp);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(path);
			free(path);
			sh_deinit(126);
		}
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
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
			if (check_path(name, 0))
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
	if (name && ms_strlen(name) == 0)
		sh_deinit(127);
	sh_deinit(EXIT_SUCCESS);
}
