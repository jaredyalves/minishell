/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:58:25 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/16 15:58:25 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

int	pipe1(int *pipes)
{
	int	status;

	status = pipe(pipes);
	if (status == -1)
		panic("pipe");
	return (status);
}
