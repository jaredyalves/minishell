#include "minishell.h"

t_cmd	*parse_line(char **p_line, char *end_line)
{
	t_cmd	*cmd;
	t_token	token;

	cmd = parse_pipe(p_line, end_line);
	if (peek(p_line, end_line, "&"))
	{
		token = get_token(p_line, end_line, NULL, NULL);
		if (token == TOKEN_SINGLE_AMPERSAND)
			cmd = background_command(cmd);
		else if (token == TOKEN_DOUBLE_AMPERSAND)
			cmd = and_command(cmd, parse_line(p_line, end_line));
	}
	if (peek(p_line, end_line, ";"))
	{
		get_token(p_line, end_line, NULL, NULL);
		cmd = sequence_command(cmd, parse_line(p_line, end_line));
	}
	return (cmd);
}
