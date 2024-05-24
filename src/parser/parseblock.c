#include "minishell.h"

t_cmd	*parseblock(char **ps, char *es)
{
	t_cmd	*cmd;

	if (!peek(ps, es, "("))
		panic("missing `('", NULL);
	get_token(ps, es, NULL, NULL);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		panic("missing `)'", cmd);
	get_token(ps, es, NULL, NULL);
	cmd = parseredir(cmd, ps, es);
	return (cmd);
}
