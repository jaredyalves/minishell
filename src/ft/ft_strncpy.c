#include "minishell.h"

char *ft_strncpy(char *dst, const char *src, size_t n)
{
	char *ptr;

	ptr = dst;
	while (n > 0 && *src != '\0')
	{
		*ptr++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*ptr++ = '\0';
		n--;
	}
	return (dst);
}
