#include "minishell.h"

char *ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	len;

	len = ft_strnlen(src, n);
	dst = (char *)malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	ft_strncpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}
