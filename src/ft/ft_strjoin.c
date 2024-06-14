#include "ft.h"
#include <stdlib.h>

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, (len + 1));
	ft_strlcat(str, s2, (len + 1));
	free(s1);
	return (str);
}
