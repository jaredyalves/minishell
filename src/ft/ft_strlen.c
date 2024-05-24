#include "minishell.h"

size_t ft_strlen(const char *s)
{
	const char *str = s;
	while (*str)
		str++;
	return str - s;
}
