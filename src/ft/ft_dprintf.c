#include <stdarg.h>
#include <unistd.h>

static int write_char(int fd, char c)
{
	return ((int)write(fd, &c, 1));
}

static int write_string(int fd, const char *s)
{
	int written;

	written = 0;
	if (!s)
		s = "(null)";
	while (*s)
		written += write_char(fd, *s++);
	return (written);
}

static int write_number(int fd, ssize_t n)
{
	int	 i;
	int	 written;
	char buffer[20];

	i = 0;
	written = 0;
	if (n < 0)
	{
		written += write_char(fd, '-');
		n = -n;
	}
	while (n > 0)
	{
		buffer[i++] = (char)(n % 10 + '0');
		n /= 10;
	}
	while (i > 0)
		written += write_char(fd, buffer[--i]);
	return written;
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
				written += write_string(fd, va_arg(args, const char *));
			else if (*p == 'd')
				written += write_number(fd, va_arg(args, int));
			else if (*p == 'c')
				written += write_char(fd, (char)va_arg(args, int));
		}
		else
			written += write_char(fd, *p);
		p++;
	}
	va_end(args);
	return written;
}
