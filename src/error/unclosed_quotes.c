#include "libft.h"
#include "minishell.h"

void	unclosed_quotes(void)
{
	t_ms	*ms;

	ms = ms_get();
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd("unclosed quotes", STDERR);
	ft_putstr_fd("\n", STDERR);
	ms->last_status = 2;
}
