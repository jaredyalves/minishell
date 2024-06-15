#include "libft.h"
#include "minishell.h"

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

static char	*parse_argument(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		token;

	token = get_token(ps, es, &q, &eq);
	if (token == 0)
		return (0);
	if (token != 'a')
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		if (token < 0)
		{
			token = -token;
			ft_putchar_fd(token, STDERR_FILENO);
		}
		ft_putchar_fd(token, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (0);
	}
	return (expand_argument(q, eq));
}

t_cmd	*parse_execute(char **ps, char *es)
{
	int			argc;
	t_cmd		*cmd;
	t_execute	*ecmd;

	if (peek(ps, es, "(", "("))
		return (parse_block(ps, es));
	argc = 0;
	ecmd = (t_execute *)execute();
	cmd = (t_cmd *)ecmd;
	cmd = parse_redirection(0, ps, es);
	while (!peek(ps, es, TOKENS, TOKENS))
	{
		if (argc >= ARG_MAX)
		{
			ft_putstr_fd("minishell: too many arguments\n", STDERR_FILENO);
			return (free_command(&cmd));
		}
		ecmd->argv[argc] = parse_argument(ps, es);
		if (!ecmd->argv[argc++])
			break ;
		cmd = parse_redirection(cmd, ps, es);
	}
	cmd = invert_redirections(cmd, ecmd);
	return (cmd);
}
