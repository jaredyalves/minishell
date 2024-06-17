#include "minishell.h"

t_cmd	*parse_list1(char **ps, char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parse_list2(ps, es);
	if (!cmd)
		return (0);
	if (peek(ps, es, "&;", ""))
	{
		token = get_token(ps, es, 0, 0);
		if (peek(ps, es, "|&;", "|&;"))
			return (free_command(&cmd));
		if (token == '&')
			cmd = list(BACKGROUND, cmd, parse_list1(ps, es));
		if (token == ';')
			cmd = list(SEQUENCE, cmd, parse_list1(ps, es));
		if (!((t_list *)cmd)->right)
			return (free_command(&cmd));
	}
	return (cmd);
}

t_cmd	*parse_list2(char **ps, char *es)
{
	t_cmd	*cmd;
	int		token;

	cmd = parse_pipeline(ps, es);
	if (!cmd)
		return (0);
	while (peek(ps, es, "", "|&"))
	{
		if (peek_next(ps, es, "|)&;", "|)&;"))
			return (free_command(&cmd));
		token = get_token(ps, es, 0, 0);
		if (token == - '&')
			cmd = list(AND_IF, cmd, parse_pipeline(ps, es));
		if (token == - '|')
			cmd = list(OR_IF, cmd, parse_pipeline(ps, es));
		if (!((t_list *)cmd)->right)
			return (free_command(&cmd));
	}
	return (cmd);
}
