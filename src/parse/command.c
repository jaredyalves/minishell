#include <linux/limits.h>

#include "minishell.h"

static t_cmd	*invert_redirections(t_cmd *cmd)
{
	t_redicmd	*prev;
	t_redicmd	*curr;
	t_redicmd	*next;

	prev = NULL;
	curr = (t_redicmd *)cmd;
	while (curr != NULL)
	{
		next = (t_redicmd *)curr->command;
		curr->command = (t_cmd *)prev;
		prev = curr;
		curr = next;
	}
	return ((t_cmd *)prev);
}

static t_cmd	*insert_execute(t_cmd *cmd, t_execcmd *ecmd)
{
	t_redicmd	*curr;

	if (cmd == NULL)
	{
		return ((t_cmd *)ecmd);
	}
	curr = (t_redicmd *)cmd;
	while (curr->command != NULL)
	{
		curr = (t_redicmd *)curr->command;
	}
	curr->command = (t_cmd *)ecmd;
	return (cmd);
}

t_cmd	*parse_command(char **ps, const char *es)
{
	char		*eq;
	char		*q;
	t_cmd		*cmd;
	t_execcmd	*ecmd;
	int			token;

	if (peek(ps, es, "(", "("))
		return (parse_block(ps, es));
	ecmd = (t_execcmd *)execute_command();
	cmd = parse_redirection(NULL, ps, es);
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
	cmd = invert_redirections(cmd);
	cmd = insert_execute(cmd, ecmd);
	return (cmd);
}
