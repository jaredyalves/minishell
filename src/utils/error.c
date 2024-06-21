/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:13:19 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:19 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	panic(char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	sh_deinit(EXIT_FAILURE);
}
