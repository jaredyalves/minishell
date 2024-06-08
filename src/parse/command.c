#include <linux/limits.h>

#include "minishell.h"

t_cmd	*parse_command(char **ps, const char *es)
{
	char		*eq;
	char		*q;
	t_cmd		*cmd;
	t_execcmd	*ecmd;
	int			token;

	if (peek(ps, es, "(", "("))
		return (parse_block(ps, es));
	cmd = execute_command();
	ecmd = (t_execcmd *)cmd;
	while (!peek(ps, es, SYMBOLS, SYMBOLS))
	{
		token = get_token(ps, es, &q, &eq);
		if (token == 0)
			break ;
		if (token != 'a')
			return (free_cmd(&cmd), NULL);
		if (ecmd->argc >= ARG_MAX)
		{
			ft_dprintf(STDERR_FILENO, "minishell: too many arguments\n");
			return (free_cmd(&cmd), NULL);
		}
		ecmd->argv[ecmd->argc] = q;
		ecmd->end_argv[ecmd->argc++] = eq;
		cmd = parse_redirection(cmd, ps, es);
	}
	return (cmd);
}
