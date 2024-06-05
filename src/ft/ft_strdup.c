#include "ft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	len;

	len = ft_strlen(s) + 1;
	d = malloc(len);
	if (!d)
		return (0);
	ft_memcpy(d, s, len);
	return (d);
}
