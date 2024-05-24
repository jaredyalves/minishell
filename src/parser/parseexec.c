#include "lexer.h"
#include "minishell.h"
#include "parser.h"

t_cmd	*parseexec(char **ps, char *es)
{
	char		*q;
	char		*eq;
	t_token		 token;
	t_execcmd	*cmd;
	t_cmd		*ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execcmd();
	cmd = (t_execcmd *)ret;
	while (!peek(ps, es, SYMBOLS))
	{
		token = get_token(ps, es, &q, &eq);
		if (token == TOKEN_NULL)
			break ;
		if (token != TOKEN_NO_SPECIAL)
			panic("syntax", ret);
		if (cmd->argc >= ARG_MAX)
			panic("too many args", ret);
		cmd->argv[cmd->argc] = q;
		cmd->eargv[cmd->argc] = eq;
		cmd->argc++;
		ret = parseredir(ret, ps, es);
	}
	return (ret);
}

// vim: ts=4 sts=4 sw=4 noet
