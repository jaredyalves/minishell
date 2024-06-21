/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by joamonte          #+#    #+#             */
/*   Updated: 2024/06/21 16:45:31 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>

int	ft_pwd(char **args)
{
	char	*directory;

	if (args[1])
	{
		ft_putstr_fd("pwd Error: too many arguments\n", 2);
		return (1);
	}
	directory = getcwd(NULL, 0);
	printf("%s\n", directory);
	free(directory);
	return (0);
}
