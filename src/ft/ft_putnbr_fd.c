#include "ft.h"

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
