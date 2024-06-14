#include "ft.h"
#include "minishell.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

void	panic(char *error)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(error, STDERR);
	if (strerror(errno))
	{
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
	}
	ft_putstr_fd("\n", STDERR);
	exit(EXIT_FAILURE);
}

int	syntax(char **ps, char *es, int allow_block, int allow_newline)
{
	char	*s;
	int		token;

	s = *ps;
	token = get_token(&s, es, 0, 0);
	if (token != 'a')
	{
		if ((token == 0 && allow_newline) || (token == '(' && allow_block))
			return (1);
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd("syntax error near unexpected token `", STDERR);
		if (token == 0)
			ft_putstr_fd("newline", STDERR);
		else if (token < 0)
		{
			token = -token;
			ft_putchar_fd(token, STDERR);
		}
		ft_putchar_fd(token, STDERR);
		ft_putstr_fd("'\n", STDERR);
		return (0);
	}
	return (1);
}
