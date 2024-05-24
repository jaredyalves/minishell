#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "run.h"
#include <fcntl.h>
#include <stddef.h>

t_cmd	*parseredir(t_cmd *cmd, char **ps, char *es)
{
	t_token	 token;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (get_token(ps, es, &q, &eq) != TOKEN_NO_SPECIAL)
		{
			freecmd(cmd);
			panic("no file");
		}
		if (token == TOKEN_SINGLE_LESS)
			cmd = redicmd(cmd, q, eq, O_RDONLY);
		else if (token == TOKEN_SINGLE_GREATER)
			cmd = redicmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC);
		else if (token == TOKEN_DOUBLE_GREATER)
			cmd = redicmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND);
	}
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
