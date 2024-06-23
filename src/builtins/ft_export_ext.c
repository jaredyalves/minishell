/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:59:22 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 21:01:45 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

static char	**copy(char **envp)
{
	int		i;
	int		count;
	char	**envp_copy;

	envp_copy = (char **) ft_calloc(ARG_MAX + 1, sizeof(char *));
	if (!envp_copy)
		panic("ft_calloc");
	count = 0;
	while (envp[count])
		count++;
	i = -1;
	while (++i < count)
		envp_copy[i] = envp[i];
	return (envp_copy);
}

static int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=' && s1[i] == s2[i])
		i++;
	if (s1[i] == '=' && s2[i] != '=')
		return ((unsigned char)0 - (unsigned char)s2[i]);
	if (s1[i] != '=' && s2[i] == '=')
		return ((unsigned char)s1[i] - (unsigned char)0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	**sort(char **envp)
{
	int		i;
	int		j;
	char	*key;
	char	**envp_copy;

	i = 1;
	envp_copy = copy(envp);
	while (envp_copy[i])
	{
		key = envp_copy[i];
		j = i - 1;
		while (j >= 0 && compare(envp_copy[j], key) > 0)
		{
			envp_copy[j + 1] = envp_copy[j];
			j = j - 1;
		}
		envp_copy[j + 1] = key;
		i++;
	}
	return (envp_copy);
}

void	print(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			ft_putchar_fd(envp[i][j++], STDOUT_FILENO);
		if (envp[i][j] == '=')
		{
			j++;
			ft_putstr_fd("=\"", STDOUT_FILENO);
			while (envp[i][j])
				ft_putchar_fd(envp[i][j++], STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free(envp);
}
