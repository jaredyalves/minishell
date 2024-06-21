/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 08:39:06 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

int	ft_export(char **new)
{
	(void)new;
	ft_putstr_fd("export: not implemented\n", STDERR_FILENO);
	return (0);
}
