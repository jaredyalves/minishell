/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:13:19 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/19 11:13:19 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_nbrlen(int n)
{
	int	i;
	int	neg;

	i = 0;
	neg = 0;
	if (n < 0)
		neg = 1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i + neg);
}

static void	ft_strrev(char *str)
{
	size_t	i;
	size_t	len;
	char	tmp;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	len;
	int		neg;
	char	*str;

	i = 0;
	neg = (n < 0);
	len = ft_nbrlen(n);
	str = ft_calloc((len + 1), sizeof(*str));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[i++] = (char)('0' + ft_abs(n % 10));
		n /= 10;
	}
	if (neg)
		str[i] = '-';
	ft_strrev(str);
	return (str);
}
