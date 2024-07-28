/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

#include <stdlib.h>
#include <sys/wait.h>

static void	move_and_copy(t_execute *ecmd, char **parsed, int *i)
{
	int	j;
	int	count;
	int argc;

	count = 0;
	while (parsed && parsed[count])
		count++;
	argc = ecmd->argc + count + - 1;

	j = ecmd->argc;
	while (j >= *i)
	{
		ecmd->argv[j + count - 1] = ecmd->argv[j];
		j--;
	}
	j = -1;
	while (++j < count)
		ecmd->argv[*i + j] = ft_strdup(parsed[j]);
	ecmd->argc = argc;
	*i += count;
}

static void	expand_command(t_execute *ecmd, int i)
{
	char	*eargv;
	char	**parsed;
	char	*expanded;

	while (ecmd->argv[i])
	{
		eargv = ecmd->argv[i] + ms_strlen(ecmd->argv[i]);
		expanded = expand_argument(ecmd->argv[i], eargv, 1);
		free(ecmd->argv[i]);
		if (expanded == NULL)
		{
			ecmd->argv[i++] = NULL;
			ecmd->argc--;
			continue;
		}
		if (ft_strchr(expanded, '\1') == NULL)
		{
			ecmd->argv[i++] = expanded;
			continue;
		}
		parsed = ft_split(expanded, '\1');
		free(expanded);
		move_and_copy(ecmd, parsed, &i);
		free_split(parsed);
	}
}

void	execute_execute(t_execute *ecmd)
{
	expand_command(ecmd, 0);
	if (is_builtin(ecmd))
	{
		if (get_sh()->subshell == 0)
			execute_builtin(ecmd);
		else if (fork1() == 0)
			execute_builtin(ecmd);
	}
	else
	{
		if (fork1() == 0)
			execute_external(ecmd);
		if (get_sh()->subshell == 0)
			wait(0);
	}
}
