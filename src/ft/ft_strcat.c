#include "minishell.h"

char	*ft_strcat(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
		*ptr++ = *src++;
	*ptr = '\0';
	return (dst);
}
