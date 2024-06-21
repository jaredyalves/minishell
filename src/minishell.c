/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
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
#include <readline/readline.h>

t_sh	*get_sh(void)
{
	static t_sh	sh;

	return (&sh);
}

static void	sh_shlvl(t_sh *sh)
{
	char	*env;
	char	*env_value;
	int		env_len;
	int		shlvl;
	int		i;

	shlvl = 0;
	env_value = ft_getenv("SHLVL");
	if (env_value)
		shlvl = ft_atoi(env_value);
	free(env_value);
	i = 0;
	while (sh->env[i] && ft_strncmp(sh->env[i], "SHLVL=", 6) != 0)
		i++;
	env_value = ft_itoa(++shlvl);
	env_len = ft_strlen(env_value) + 7;
	env = (char *)ft_calloc(env_len, sizeof(char));
	if (!env)
		panic("ft_calloc");
	ft_strlcpy(env, "SHLVL=", env_len);
	ft_strlcat(env, env_value, env_len);
	free(env_value);
	free(sh->env[i]);
	sh->env[i] = env;
}

static void	sh_env(t_sh *sh, char *envp[])
{
	int	env_count;
	int	i;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	if (env_count >= ARG_MAX)
		panic("too many environment variables");
	i = 0;
	while (i < env_count)
	{
		sh->env[i] = ft_strdup(envp[i]);
		i++;
	}
	sh_shlvl(sh);
}

void	sh_init(int argc, char *argv[], char *envp[])
{
	t_sh	*sh;

	(void)argc;
	(void)argv;
	sh = get_sh();
	if (sh && !sh->init)
	{
		ft_bzero(sh, sizeof(*sh));
		sh->init = 1;
		sh_env(sh, envp);
		handle_signals();
	}
}

void	sh_deinit(int status)
{
	t_sh	*sh;
	int		i;

	sh = get_sh();
	if (sh && sh->init)
	{
		if (sh->str)
			free(sh->str);
		i = 0;
		while (sh->env[i])
			free(sh->env[i++]);
		if (sh->cmd)
			free_command(&sh->cmd);
		ft_bzero(sh, sizeof(*sh));
		rl_clear_history();
	}
	exit(status);
}
