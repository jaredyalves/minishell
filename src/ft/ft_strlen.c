#include <stddef.h>

size_t ft_strlen(const char *s)
{
	const char *str = s;
	while (*str)
		str++;
	return str - s;
}

// vim: ts=4 sts=4 sw=4 noet
