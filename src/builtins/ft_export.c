/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 22:22:16 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

char	**sort(char **envp);
void	print(char **envp);

static int	is_valid(char *env)
{
	int		i;

	i = 0;
	if (env[i] == '=')
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (i == 0 && !(ft_isalpha(env[i]) || env[i] == '_'))
			return (0);
		if (!(ft_isalnum(env[i]) || env[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	add(char **envp, char *env)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (i + 1 >= ARG_MAX)
	{
		ft_putstr_fd("minishell: export: ", STDERR_FILENO);
		ft_putstr_fd("too many environment variables\n", STDERR_FILENO);
		return (1);
	}
	envp[i] = ft_strdup(env);
	if (!envp[i])
		return (1);
	return (0);
}

static int	update(char **envp, char *env)
{
	size_t	i;
	size_t	len;
	char	*name;
	char	*start;

	start = env;
	while (*env && *env != '=')
		env++;
	len = env - start + 1;
	name = (char *) ft_calloc(len, sizeof(char));
	if (!name)
		panic("ft_calloc");
	ft_strlcpy(name, start, len);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], name, len - 1) != 0)
		i++;
	if (!envp[i])
		return (free(name), 1);
	free(envp[i]);
	envp[i] = ft_strdup(start);
	free(name);
	return (0);
}

int	ft_export(char **args)
{
	int		status;

	status = 0;
	if (!args[1])
		return (print(sort(get_sh()->env)), 0);
	while (*++args)
	{
		if (!is_valid(*args))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(*args, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			status = 1;
			continue ;
		}
		status = update(get_sh()->env, *args);
		if (status != 0)
			status = add(get_sh()->env, *args);
		if (status == 1)
			break ;
	}
	return (status);
}
