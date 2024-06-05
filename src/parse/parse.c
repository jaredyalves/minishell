#include "minishell.h"

t_cmd	*parse(char *str)
{
	char	*s;
	char	*es;
	t_cmd	*cmd;

	s = str;
	es = s + ft_strlen(s);
	cmd = parse_list(&s, es);
	terminate(cmd);
	return (cmd);
}

t_cmd	*parse_list(char **ps, const char *es)
{
	const t_token	to_search[] = {TOKEN_DOUBLE_AMPERSAND,
		TOKEN_SINGLE_AMPERSAND, TOKEN_DOUBLE_PIPE, TOKEN_SINGLE_SEMICOLON,
		TOKEN_NULL};
	const t_token	exeptions[] = {TOKEN_WORD, TOKEN_NULL,
		TOKEN_LEFT_PARENTHESES, TOKEN_QUOTE};
	t_cmd			*command;
	t_token			token;

	command = parse_pipeline(ps, es);
	if (find_token(ps, es, to_search))
	{
		token = get_token(ps, es, NULL, NULL);
		if (find_token(ps, es, exeptions))
			return (free_cmd(&command), NULL);
		if (token == TOKEN_DOUBLE_AMPERSAND)
			command = logical_command(TYPE_AND, command, parse_list(ps, es));
		if (token == TOKEN_SINGLE_AMPERSAND)
			command = background_command(command);
		if (token == TOKEN_DOUBLE_PIPE)
			command = logical_command(TYPE_OR, command, parse_list(ps, es));
		if (token == TOKEN_SINGLE_SEMICOLON)
			command = logical_command(TYPE_SEQUENCE, command, parse_list(ps, es));
	}
	return (command);
}

t_cmd	*parse_pipeline(char **ps, const char *es)
{
	const t_token	to_search[] = {TOKEN_SINGLE_PIPE, TOKEN_NULL};
	t_cmd			*command;
	t_token			token;

	command = parse_command(ps, es);
	if (find_token(ps, es, to_search))
	{
		token = get_token(ps, es, NULL, NULL);
		if (peek_token(ps, es, 0) != TOKEN_WORD && peek_token(ps, es,
				0) != TOKEN_NULL)
			return (free_cmd(&command), NULL);
		if (token == TOKEN_SINGLE_PIPE)
			command = logical_command(TYPE_PIPE, command, parse_pipeline(ps, es));
	}
	return (command);
}

t_cmd	*parse_command(char **ps, const char *es)
{
	char		*eq;
	char		*q;
	t_cmd		*command;
	t_execcmd	*e_command;

	if (peek_token(ps, es, 0) == TOKEN_LEFT_PARENTHESES)
		return (parse_block(ps, es));
	command = execute_command();
	e_command = (t_execcmd *)command;
	while (peek_token(ps, es, 0) == TOKEN_WORD || peek_token(ps, es, 0) == TOKEN_QUOTE)
	{
		get_token(ps, es, &q, &eq);
		if (e_command->argc >= ARG_MAX)
		{
			ft_dprintf(STDERR_FILENO, "minishell: too many arguments\n");
			return (free_cmd(&command), NULL);
		}
		e_command->argv[e_command->argc] = q;
		e_command->end_argv[e_command->argc] = eq;
		e_command->argc++;
		command = parse_redirection(command, ps, es);
	}
	return (command);
}

t_cmd	*parse_redirection(t_cmd *command, char **ps, const char *es)
{
	const t_token	to_search[] = {TOKEN_DOUBLE_GREATER, TOKEN_SINGLE_GREATER,
		TOKEN_DOUBLE_LESS, TOKEN_SINGLE_LESS, TOKEN_NULL};
	char			*eq;
	char			*q;
	t_token			token;

	if (find_token(ps, es, to_search))
	{
		token = get_token(ps, es, NULL, NULL);
		if (peek_token(ps, es, 0) != TOKEN_WORD)
			return (free_cmd(&command), NULL);
		get_token(ps, es, &q, &eq);
		if (token == TOKEN_DOUBLE_GREATER)
			command = redirect_command(command, q, eq,
					O_WRONLY | O_CREAT | O_APPEND);
		if (token == TOKEN_SINGLE_GREATER)
			command = redirect_command(command, q, eq,
					O_WRONLY | O_CREAT | O_TRUNC);
		if (token == TOKEN_SINGLE_LESS)
			command = redirect_command(command, q, eq, O_RDONLY);
	}
	return (command);
}

t_cmd	*parse_block(char **ps, const char *es)
{
	t_cmd	*command;

	get_token(ps, es, NULL, NULL);
	if (peek_token(ps, es, 0) != TOKEN_WORD)
		return (NULL);
	command = parse_list(ps, es);
	if (peek_token(ps, es, 0) != TOKEN_RIGHT_PARENTHESES)
		return (free_cmd(&command), NULL);
	get_token(ps, es, NULL, NULL);
	return (command);
}
