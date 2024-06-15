#include "libft.h"
#include "minishell.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	panic(char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	if (strerror(errno))
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	check_syntax(char **ps, char *es, int block, int newline)
{
	char	*s;
	int		token;

	s = *ps;
	token = get_token(&s, es, 0, 0);
	if (token != 'a')
	{
		if ((token == 0 && newline) || (token == '(' && block))
			return (1);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		if (token == 0)
			ft_putstr_fd("newline", STDERR_FILENO);
		else if (token < 0)
		{
			token = -token;
			ft_putchar_fd(token, STDERR_FILENO);
		}
		ft_putchar_fd(token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}
