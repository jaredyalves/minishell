#include "minishell.h"

t_cmd	*parse_cmdline(char *cmdline)
{
	char	*s;
	char	*es;
	t_cmd	*command;

	s = cmdline;
	es = s + ft_strlen(s);
	command = parse_list(&s, es);
	terminate_command(command);
	return (command);
}

t_cmd	*parse_list(char **ps, const char *es)
{
	const t_token	to_search[] = {TOKEN_DOUBLE_AMPERSAND,
		TOKEN_SINGLE_AMPERSAND, TOKEN_DOUBLE_PIPE, TOKEN_SINGLE_SEMICOLON,
		TOKEN_NULL};
	t_cmd			*command;
	t_token			token;

	command = parse_pipeline(ps, es);
	if (find_token(ps, es, to_search))
	{
		token = get_token(ps, es, NULL, NULL);
		if (peek_token(ps, es, 0) != TOKEN_WORD
			&& peek_token(ps, es, 0) != TOKEN_NULL)
			return (free_command(command), NULL);
		if (token == TOKEN_DOUBLE_AMPERSAND)
			command = and_command(command, parse_list(ps, es));
		if (token == TOKEN_SINGLE_AMPERSAND)
			command = background_command(command);
		if (token == TOKEN_DOUBLE_PIPE)
			command = or_command(command, parse_list(ps, es));
		if (token == TOKEN_SINGLE_SEMICOLON)
			command = sequence_command(command, parse_list(ps, es));
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
			return (free_command(command), NULL);
		if (token == TOKEN_SINGLE_PIPE)
			command = pipe_command(command, parse_pipeline(ps, es));
	}
	return (command);
}

t_cmd	*parse_command(char **ps, const char *es)
{
	char		*eq;
	char		*q;
	t_cmd		*command;
	t_execcmd	*e_command;

	command = execute_command();
	e_command = (t_execcmd *)command;
	while (peek_token(ps, es, 0) == TOKEN_WORD)
	{
		get_token(ps, es, &q, &eq);
		if (e_command->argc >= ARG_MAX)
		{
			ft_dprintf(STDERR_FILENO, "minishell: too many arguments\n");
			return (free_command(command), NULL);
		}
		e_command->argv[e_command->argc] = q;
		e_command->eargv[e_command->argc] = eq;
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
			return (free_command(command), NULL);
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
