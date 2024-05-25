#include "minishell.h"

int	parse_arguments(t_execcmd *e_command, char **ps, char *es)
{
	char	*q;
	char	*eq;
	t_token	token;

	token = get_token(ps, es, &q, &eq);
	if (token == TOKEN_NULL)
		return (1);
	if (token != TOKEN_NO_SPECIAL)
		panic("syntax", (t_cmd *)e_command);
	if (e_command->argc >= ARG_MAX)
		panic("too many arguments", (t_cmd *)e_command);
	e_command->argv[e_command->argc] = q;
	e_command->eargv[e_command->argc] = eq;
	e_command->argc++;
	return (0);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd		*command;
	t_execcmd	*e_command;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	command = execute_command();
	e_command = (t_execcmd *)command;
	while (!peek(ps, es, SYMBOLS))
	{
		if (parse_arguments(e_command, ps, es))
			break ;
		command = parseredir(command, ps, es);
	}
	return (command);
}
