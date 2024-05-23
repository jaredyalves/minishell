#include "ft.h"
#include <stdio.h>
#include <unistd.h>

static int printf_c(int fd, char c)
{
	return ((int)write(fd, &c, 1));
}

static int printf_s(int fd, const char *s)
{
	int written;

	written = 0;
	if (s == NULL)
		written += printf_s(fd, "(null)");
	while (s != NULL && s[written] != '\0')
		written += printf_c(fd, s[written]);
	return (written);
}

static int printf_d(int fd, ssize_t n)
{
	int written;

	written = 0;
	if (n < 0)
	{
		written += printf_c(fd, '-');
		n = -n;
	}
	if (n < 10)
		written += printf_c(fd, (char)(n + '0'));
	else
	{
		written += printf_d(fd, n / 10);
		written += printf_c(fd, (char)((n % 10) + '0'));
	}
	return (written);
}

int ft_dprintf(int fd, const char *format, ...)
{
	const char *p;
	int			written;
	va_list		args;

	p = format;
	written = 0;
	va_start(args, format);
	while (*p)
	{
		if (*p == '%' && *(p + 1))
		{
			p++;
			if (*p == 's')
				written += printf_s(fd, va_arg(args, const char *));
			else if (*p == 'd')
				written += printf_d(fd, va_arg(args, int));
			else if (*p == 'c')
				written += printf_c(fd, (char)va_arg(args, int));
		}
		else
			written += printf_c(fd, *p);
		p++;
	}
	va_end(args);
	return written;
}

// vim: ts=4 sts=4 sw=4 noet
