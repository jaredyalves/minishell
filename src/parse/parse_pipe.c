#include "minishell.h"

t_cmd	*parse_pipe(char **p_line, char *end_line)
{
	t_cmd	*cmd;
	t_token	token;

	cmd = parse_execute(p_line, end_line);
	if (peek(p_line, end_line, "|"))
	{
		token = get_token(p_line, end_line, NULL, NULL);
		if (token == TOKEN_SINGLE_PIPE)
			cmd = pipe_command(cmd, parse_pipe(p_line, end_line));
		else if (token == TOKEN_DOUBLE_PIPE)
			cmd = or_command(cmd, parse_line(p_line, end_line));
	}
	return (cmd);
}
