/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcapistr <jcapistr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:50:48 by jcapistr          #+#    #+#             */
/*   Updated: 2022/11/24 11:59:13 by jcapistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	ln;

	ln = n;
	if (ln < 0)
	{
		ln *= -1;
		ft_putchar_fd('-', fd);
	}
	if (ln < 10)
		ft_putchar_fd((char)(ln + '0'), fd);
	else
	{
		ft_putnbr_fd((int)(ln / 10), fd);
		ft_putchar_fd((char)((ln % 10) + '0'), fd);
	}
}
