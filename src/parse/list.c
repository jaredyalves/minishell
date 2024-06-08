#include "minishell.h"

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
