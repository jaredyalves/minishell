#include "../lexer/lexer.h"
#include "../minishell.h"
#include "parser.h"
#include "run/run.h"
#include <fcntl.h>

t_cmd	*parseredir(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = get_token(ps, es, 0, 0);
		if (get_token(ps, es, &q, &eq) != 'a')
		{
			freecmd(cmd);
			panic("minishell: no file for redirection");
		}
		if (tok == '<')
			cmd = redicmd(cmd, q, eq, O_RDONLY);
		else if (tok == '>')
			cmd = redicmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC);
		else if (tok == '+')
			cmd = redicmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND);
	}
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
