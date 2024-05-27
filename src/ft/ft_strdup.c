#include "minishell.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(src) + 1;
	dst = (char *)malloc(len);
	if (!dst)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}
