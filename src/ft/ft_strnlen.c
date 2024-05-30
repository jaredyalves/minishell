#include "minishell.h"

size_t ft_strnlen(const char *s, size_t n)
{
	const char *p;

	p = s;
	while (n-- && *p != '\0')
		p++;
	return (p - s);
}