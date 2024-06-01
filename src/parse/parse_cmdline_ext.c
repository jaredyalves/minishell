#include "minishell.h"

t_cmd	*parse_block(char **ps, const char *es)
{
	t_cmd	*command;

	get_token(ps, es, NULL, NULL);
	if (peek_token(ps, es, 0) != TOKEN_WORD)
		return (NULL);
	command = parse_list(ps, es);
	if (peek_token(ps, es, 0) != TOKEN_RIGHT_PARENTHESES)
		return (free_command(command), NULL);
	get_token(ps, es, NULL, NULL);
	return (command);
}
