#include "minishell.h"

t_cmd	*parse(char *str)
{
	char	*es;
	t_cmd	*cmd;

	es = str + ft_strlen(str);
	cmd = parse_list(&str, es);
	if (cmd == NULL)
		return (NULL);
	peek(&str, es, "", "");
	if (str != es)
	{
		ft_dprintf(STDERR_FILENO, "leftovers: %s\n", str);
		free_cmd(&cmd);
		return (NULL);
	}
	terminate(cmd);
	return (cmd);
}

t_cmd	*parse_list(char **ps, const char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parse_pipeline(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (peek(ps, es, "&;", "&|"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (peek(ps, es, "<|>&;", "<|>&;"))
			return (free_cmd(&cmd), NULL);
		if (token == '&')
			cmd = background_command(cmd);
		else if (token == - '&')
			cmd = logical_command(TYPE_AND, cmd, parse_list(ps, es));
		else if (token == ';')
			cmd = logical_command(TYPE_SEQUENCE, cmd, parse_list(ps, es));
		else if (token == - '|')
			cmd = logical_command(TYPE_OR, cmd, parse_list(ps, es));
	}
	return (cmd);
}

t_cmd	*parse_pipeline(char **ps, const char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parse_command(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (peek(ps, es, "|", ""))
	{
		token = get_token(ps, es, NULL, NULL);
		if (peek(ps, es, "<|>&;", "<|>&;"))
			return (free_cmd(&cmd), NULL);
		if (token == '|')
			cmd = logical_command(TYPE_PIPE, cmd, parse_pipeline(ps, es));
	}
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

t_cmd	*parse_redirection(t_cmd *cmd, char **ps, const char *es)
{
	char	*eq;
	char	*q;
	int		token;

	while (peek(ps, es, "<>", "<>"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (get_token(ps, es, &q, &eq) != 'a')
			return (free_cmd(&cmd), NULL);
		if (token == - '>')
			cmd = redirect_command(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND);
		else if (token == '>')
			cmd = redirect_command(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC);
		else if (token == '<')
			cmd = redirect_command(cmd, q, eq, O_RDONLY);
		else if (token == - '<')
			cmd = heredoc_command(cmd, q, eq);
	}
	return (cmd);
}

t_cmd	*parse_block(char **ps, const char *es)
{
	t_cmd	*cmd;

	get_token(ps, es, NULL, NULL);
	cmd = parse_list(ps, es);
	if (cmd == NULL)
		return (NULL);
	if (!peek(ps, es, ")", ")"))
		return (free_cmd(&cmd), NULL);
	get_token(ps, es, NULL, NULL);
	cmd = parse_redirection(cmd, ps, es);
	return (cmd);
}
