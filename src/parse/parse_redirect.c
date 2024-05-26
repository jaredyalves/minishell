#include "minishell.h"

t_cmd	*parse_redirect(t_cmd *command, char **p_line, char *end_line)
{
	t_token	token;
	char	*q;
	char	*eq;

	while (peek(p_line, end_line, "<>"))
	{
		token = get_token(p_line, end_line, NULL, NULL);
		if (get_token(p_line, end_line, &q, &eq) != TOKEN_NO_SPECIAL)
			panic("missing file for redirection", command);
		if (token == TOKEN_SINGLE_LESS)
			command = redirect_command(command, q, eq, O_RDONLY);
		else if (token == TOKEN_SINGLE_GREATER)
			command = redirect_command(command, q, eq,
					O_WRONLY | O_CREAT | O_TRUNC);
		else if (token == TOKEN_DOUBLE_GREATER)
			command = redirect_command(command, q, eq,
					O_WRONLY | O_CREAT | O_APPEND);
	}
	return (command);
}
