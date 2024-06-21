/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

static void	execute_sequence(t_list *lcmd)
{
	execute_command(lcmd->left);
	wait(0);
	execute_command(lcmd->right);
	wait(0);
}

static void	execute_background(t_list *lcmd)
{
	if (fork1() == 0)
	{
		close(STDIN_FILENO);
		open("/dev/null", O_RDONLY);
		execute_command(lcmd->left);
	}
	waitpid(-1, 0, WNOHANG);
	get_sh()->exit_status = 0;
	execute_command(lcmd->right);
}

static void	execute_and_if(t_list *lcmd)
{
	execute_command(lcmd->left);
	wait(0);
	if (get_sh()->exit_status == 0)
	{
		execute_command(lcmd->right);
		wait(0);
	}
}

static void	execute_or_if(t_list *lcmd)
{
	execute_command(lcmd->left);
	wait(0);
	if (get_sh()->exit_status != 0)
	{
		execute_command(lcmd->right);
		wait(0);
	}
}

void	execute_list(t_list *lcmd)
{
	if (lcmd)
	{
		if (lcmd->subtype == SEQUENCE)
			execute_sequence(lcmd);
		if (lcmd->subtype == BACKGROUND)
			execute_background(lcmd);
		if (lcmd->subtype == AND_IF)
			execute_and_if(lcmd);
		if (lcmd->subtype == OR_IF)
			execute_or_if(lcmd);
	}
}
