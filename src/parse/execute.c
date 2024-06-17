#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static t_cmd	*invert_redirections(t_cmd *cmd, t_execute *ecmd)
{
	t_redirection	*prev;
	t_redirection	*curr;
	t_redirection	*next;

	prev = 0;
	curr = (t_redirection *)cmd;
	while (curr)
	{
		next = (t_redirection *)curr->cmd;
		curr->cmd = (t_cmd *)prev;
		prev = curr;
		curr = next;
	}
	if (!prev)
		return ((t_cmd *)ecmd);
	curr = prev;
	while (curr->cmd)
		curr = (t_redirection *)curr->cmd;
	curr->cmd = (t_cmd *)ecmd;
	return ((t_cmd *)prev);
}

static char	*parse_argument(char **ps, char *es, int *error)
{
	char	*q;
	char	*eq;
	int		token;

	token = get_token(ps, es, &q, &eq);
	if (token == 0)
		return (*error = 0, (char *)0);
	if (token != 'a')
		return (*error = 1, (char *)0);
	return (*error = 0, expand_argument(q, eq));
}

static t_cmd	*cleanup(t_cmd *cmd, t_execute *ecmd)
{
	free_command(&cmd);
	cmd = (t_cmd *)ecmd;
	free_command(&cmd);
	return (0);
}

t_cmd	*parse_execute(char **ps, char *es)
{
	t_cmd		*cmd;
	t_execute	*ecmd;
	char		*arg;
	int			error;

	if (peek(ps, es, "(", "("))
		return (parse_block(ps, es));
	ecmd = (t_execute *)execute();
	cmd = parse_redirection(0, ps, es);
	while (!peek(ps, es, TOKENS, TOKENS))
	{
		if (ecmd->argc >= ARG_MAX)
			return (ft_putstr_fd("minishell: too many arguments\n",
					STDERR_FILENO), free_command(&cmd));
		arg = parse_argument(ps, es, &error);
		if (!arg && !error)
			break ;
		if (!arg && error)
			return (cleanup(cmd, ecmd));
		ecmd->argv[ecmd->argc++] = arg;
		cmd = parse_redirection(cmd, ps, es);
	}
	if (!cmd && peek(ps, es, "<>", "<>"))
		return (get_token(ps, es, 0, 0), cleanup(cmd, ecmd));
	return (invert_redirections(cmd, ecmd));
}
