#include "minishell.h"

static size_t	write_char(int fd, char c)
{
	return (write(fd, &c, 1));
}

static size_t	write_string(int fd, const char *s)
{
	size_t	written;

	written = 0;
	if (!s)
		s = "(null)";
	while (*s)
		written += write(fd, s++, 1);
	return (written);
}

static size_t	write_number(int fd, ssize_t n)
{
	int		i;
	size_t	written;
	char	buffer[65];

	i = 0;
	written = 0;
	if (n < 0)
	{
		n = -n;
		written += write(fd, "-", 1);
	}
	if (n == 0)
		buffer[i++] = '0';
	else
	{
		while (n > 0)
		{
			buffer[i++] = (char)(n % 10 + '0');
			n /= 10;
		}
	}
	while (i > 0)
		written += write(fd, &(buffer[--i]), 1);
	return (written);
}

size_t	ft_dprintf(int fd, const char *format, ...)
{
	const char	*p;
	size_t		written;
	va_list		args;

	p = format;
	written = 0;
	va_start(args, format);
	while (*p)
	{
		if (*p == '%' && *(p + 1))
		{
			p++;
			if (*p == 'c')
				written += write_char(fd, va_arg(args, int));
			if (*p == 's')
				written += write_string(fd, va_arg(args, const char *));
			if (*p == 'd')
				written += write_number(fd, va_arg(args, int));
		}
		else
			written += write(fd, p, 1);
		p++;
	}
	va_end(args);
	return (written);
}
