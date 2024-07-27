#include "minishell.h"

void	parse_line(t_ms *ms, char **line_ptr, char *line_end)
{
	int token;

	(void)ms;
	token = get_token(&(*line_ptr), line_end, NULL, NULL);
	if (token != TOK_WORD)
		return (unexpected_token(token));
}
