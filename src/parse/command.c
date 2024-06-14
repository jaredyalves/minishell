#include "ft.h"
#include "minishell.h"

static void	check_leftovers(char **ps, char *es)
{
	char	*s;

	s = *ps;
	peek(&s, es, "", "");
	if (s != es)
	{
		ft_putstr_fd("minishell: leftovers: ", STDERR);
		ft_putstr_fd(s, STDERR);
		ft_putstr_fd("\n", STDERR);
	}
	*ps = s;
}

t_cmd	*parse_command(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parse_list1(&s, es);
	if (!cmd)
		return (0);
	check_leftovers(&s, es);
	return (cmd);
}
