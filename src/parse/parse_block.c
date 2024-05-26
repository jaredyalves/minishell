#include "minishell.h"

t_cmd	*parse_block(char **p_line, char *end_line)
{
	t_cmd	*cmd;

	if (!peek(p_line, end_line, "("))
		panic("missing `('", NULL);
	get_token(p_line, end_line, NULL, NULL);
	cmd = parse_line(p_line, end_line);
	if (!peek(p_line, end_line, ")"))
		panic("missing `)'", cmd);
	get_token(p_line, end_line, NULL, NULL);
	cmd = parse_redirect(cmd, p_line, end_line);
	return (cmd);
}
