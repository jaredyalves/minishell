#include "libft.h"
#include "minishell.h"

#include <stdlib.h>

void	unexpected_token(int token)
{
	t_ms	*ms;
	char	*token_string;

	ms = ms_get();
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd("syntax error near unexpected token `", STDERR);
	token_string = ms_strtok(token);
	ft_putstr_fd(token_string, STDERR);
	free(token_string);
	ft_putstr_fd("'", STDERR);
	ft_putstr_fd("\n", STDERR);
	// parse_clear(ms);
	ms->last_status = 2;
}
