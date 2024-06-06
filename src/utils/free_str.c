#include <stdlib.h>

void	free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
