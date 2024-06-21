/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->type == EXECUTE)
			execute_execute((t_execute *)cmd);
		if (cmd->type == REDIRECTION)
			execute_redirection((t_redirection *)cmd);
		if (cmd->type == LIST)
			execute_list((t_list *)cmd);
		if (cmd->type == PIPELINE)
			execute_pipeline((t_pipeline *)cmd);
	}
}
