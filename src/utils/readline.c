/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:01:44 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/20 12:04:41 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

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
