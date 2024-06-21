/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:01:44 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 16:29:48 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

static char	*getl(char *line)
{
	int		i;
	ssize_t	cc;
	char	c;

	i = 0;
	while (i + 1 < 4096)
	{
		cc = read(0, &c, 1);
		if (cc < 1)
			break ;
		line[i++] = c;
		if (c == '\n' || c == '\r')
			break ;
	}
	line[i] = '\0';
	return (line);
}

char	*get_line(char *prompt)
{
	int		i;
	char	*line;
	char	*stripped;

	line = (char *)ft_calloc(4096, sizeof(char));
	if (!line)
		panic("ft_calloc");
	ft_putstr_fd(prompt, 0);
	getl(line);
	if (!line[0])
		return (free(line), (char *)0);
	i = 0;
	while (line[i])
		i++;
	if (line[i] == '\n' || line[i] == '\0')
	{
		stripped = (char *)ft_calloc(4096, sizeof(char));
		ft_strlcpy(stripped, line, i);
		free(line);
		return (stripped);
	}
	return (line);
}

void	get_str(void)
{
	t_sh	*sh;

	sh = get_sh();
	if (sh->str)
	{
		free(sh->str);
		sh->str = 0;
	}
	sh->str = readline("$ ");
	if (sh->str && *sh->str)
		add_history(sh->str);
}
