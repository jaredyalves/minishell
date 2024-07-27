#include "libft.h"
#include "minishell.h"

char	*ms_strtok(int token)
{
	char	*buffer;

	buffer = (char *)ft_calloc(MAX_INPUT, sizeof(char));
	if (buffer == NULL)
		panic("ft_calloc");
	if (token == TOK_NULL)
		ft_strlcpy(buffer, "newline", MAX_INPUT);
	else if (token == TOK_WORD)
		ft_strlcpy(buffer, "word", MAX_INPUT);
	else if (token < 0)
	{
		buffer[0] = (char)-token;
		buffer[1] = (char)-token;
	}
	else
		buffer[0] = (char)token;
	return (buffer);
}
